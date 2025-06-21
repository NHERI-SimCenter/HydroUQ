import pip

def import_or_install(package):
    try:
        __import__(package)
    except ImportError:
        try:
            print(f"Installing {package} using pip without --user flag...")
            pip.main(['install', package])  
        except:
            try:
                print(f"Installing {package} using pip with --user flag...")
                pip.main(['install', '--user', package])  # Try user install if system install fails
            except:
                print(f"Installing {package} using subprocess...")
                import subprocess
                subprocess.check_call(['pip', 'install', package]) 

import_or_install('PIL')
import_or_install('numpy')
import_or_install('matplotlib')
import_or_install('scipy')
import_or_install('requests')
import_or_install('geographiclib')
import_or_install('geopy')
import_or_install('brails')
import_or_install('netCDF4')
import argparse
from multiprocessing import Process
import requests
import os
import math

from PIL import Image, ImageDraw, ImageOps
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as clr
from scipy.spatial import KDTree

from geopy.geocoders import Nominatim
# from vincenty import vincenty # more accurate than methods like the Haverside function, that assume a 'spherical earth'/'great circle distance'
from geographiclib.geodesic import Geodesic # using Karney's root-finding reformulation of Vincenty's formula to leverage newton's method and greater stability at antipodal points.
from netCDF4 import Dataset # for getting sea level anomaly data 

from brails import Importer
from config_init import create_config
from wavemaker import create_waves

def _download_dem(bbox, out_path,
                 image_format='tiff',
                 pixel_type=None, # F32: floating point 32 bit, could also do U8 for unsigned 8 bit
                 resolution_factor=None, # arbitrarily chosen at the moment
                 size=None,
                 interpolation=None,
                 compression=None,
                 compression_quality=None):
    """
    Download a DEM from NOAA's global mosaic.

    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
        out_path: file path to save the image (should have correct extension)
        image_format: output format string, e.g. 'tiff', 'jpgpng'
        pixel_type: e.g. 'F32' (float32)
        resolution_factor: number of pixels per degree of longitude/latitude
        size: tuple of (width, height), overrides resolution_factor
        interpolation: e.g. 'RSP_BilinearInterpolation'
        compression: e.g. 'LZ77' (for TIFF)
        compression_quality: integer 0–100
    """
    if not resolution_factor and not size: raise Exception("No resolution or size specified for pixel count")
    base_url = (
        "https://gis.ngdc.noaa.gov/arcgis/rest/services/"
        "DEM_mosaics/DEM_global_mosaic/ImageServer/exportImage"
    )
    max_width = 20000 # Max Height: 20000, Max Width: 20000
    max_height = 20000 # Max Height: 20000, Max Width: 20000
    params = {
        "bbox": ",".join(map(str, bbox)), # "bbox" = "<xmin>,<ymin>,<xmax>,<ymax>"
        "f": "image",        # return raw image bytes
        "format": image_format,
        "bboxSR": '4326',  
        "size": f'{min(int((abs(bbox[2]-bbox[0])*resolution_factor)), max_width)},{min(int((abs(bbox[3]-bbox[1])*resolution_factor)), max_height)}',  # 'size' = '<width>, <height>' (Max Height: 20000, Max Width: 20000)
        "imageSR": '4326',
    }
    # Optional params
    if interpolation:
        params["interpolation"] = interpolation
    if compression:
        params["compression"] = compression
    if compression_quality:
        params["compressionQuality"] = compression_quality
    if pixel_type:
        params["pixelType"] = pixel_type
    if size:
        params["size"] = ",".join(map(str, size))

    # Make the request
    resp = requests.get(base_url, params=params, stream=True)
    resp.raise_for_status()
    
    # Save to disk
    with open(out_path, "wb") as f:
        for chunk in resp.iter_content(): # consider specifying chunk_size=8192
            f.write(chunk)
    print(f"Saved DEM to {out_path}")

def get_dem(bbox, out_path, 
            size=None,
            pixel_type=None,
            resolution_factor=None,
            interpolation=None):
    """
    Wrapper function for download_dem, implements wraparound.

    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
        out_path: file path to save the image (should have correct extension)
        size: tuple of (width, height), overrides resolution_factor
        pixel_type: e.g. 'F32' (float32)
        resolution_factor: number of pixels per degree of longitude/latitude
        interpolation: e.g. 'RSP_BilinearInterpolation'
        max_size: maximum pixel limit
    """
    # valid domain check
    if not resolution_factor and not size: raise Exception("No resolution or size specified for pixel count")
    if bbox[0] > 180 or bbox[2] > 180 or bbox[0] < -179.99999741594172 or bbox[2] < -179.99999741594172 or abs(bbox[1]) > 90 or abs(bbox[3]) > 90:
        raise Exception("Lat/Lng outside of validrange")

    # wraparound check
    if bbox[0] > bbox[2]:
        left_patch = (bbox[0], bbox[1], 180, bbox[3])
        if size: 
            leftwidth = int(((180 - bbox[0])*size[0])/(359.99999741594172 - (bbox[0]-bbox[2]))) # rounding like this can lose a pixel... TODO
            _download_dem(left_patch, "./mergebuffer/left.tiff", resolution_factor = resolution_factor, size = (leftwidth, size[1]), pixel_type=pixel_type, interpolation = interpolation) # need to set size
        else:
            _download_dem(left_patch, "./mergebuffer/left.tiff", resolution_factor = resolution_factor, pixel_type=pixel_type, interpolation = interpolation) # need to set size
        right_patch = (-179.99999741594172, bbox[1], bbox[2], bbox[3])
        if size: 
            rightwidth = int(((bbox[0] + 179.99999741594172)*size[0])/(359.99999741594172 - (bbox[0]-bbox[2])))
            _download_dem(right_patch, "./mergebuffer/right.tiff", resolution_factor = resolution_factor, size = (rightwidth, size[1]), pixel_type=pixel_type, interpolation = interpolation) # need to set size
        else:
            _download_dem(right_patch, "./mergebuffer/right.tiff", resolution_factor = resolution_factor, pixel_type=pixel_type, interpolation = interpolation) # need to set size
        left_img = Image.open("./mergebuffer/left.tiff")
        # os.remove("./mergebuffer/left.tiff") # keep images for now to debug
        right_img = Image.open("./mergebuffer/right.tiff")
        # os.remove("./mergebuffer/right.tiff") # keep images for now to debug
        if left_img.height != right_img.height:
            raise ValueError("Something is terribly wrong")

        new_width = left_img.width + right_img.width
        new_image = Image.new("F", (new_width, left_img.height))
        new_image.paste(left_img, (0, 0))
        new_image.paste(right_img, (left_img.width, 0))
        new_image.save(out_path)

    else:
        _download_dem(bbox, out_path, resolution_factor = resolution_factor, size = size, pixel_type=pixel_type, interpolation = interpolation) # need to set size

def combine_inventories(inventory, other_inventory):
    flag_NA = False
    centroid_to_features = {}
    centroids = []
    for assetid in other_inventory.inventory.keys():
        footprints = other_inventory.inventory[assetid].coordinates
        centroid = [sum(footprint[0] for footprint in footprints) / len(footprints), sum(footprint[1] for footprint in footprints) / len(footprints)]
        centroids.append(centroid)
        centroid_to_features[str(centroid)] = other_inventory.inventory[assetid].features # there's an implicit convexity assumption here
    quadtree = KDTree(centroids)
    for assetid in inventory.inventory.keys():
        if inventory.inventory[assetid].features.get("buildingheight", "NA") == "NA":
            footprints = inventory.inventory[assetid].coordinates
            centroid = [sum(footprint[0] for footprint in footprints) / len(footprints), sum(footprint[1] for footprint in footprints) / len(footprints)]
            dd, ii = quadtree.query(centroid, k=1, workers=-1)
            dx_m = 111111*math.cos(centroid[1]) # this is the simplified conversion factor from degrees to meters at the centroid's latitude
            dy_m = 111111
            # dx_m = 111412.84*math.cos((centroid[1] - centroids[ii][1])) - 93.5*math.cos(3*(centroid[1] - centroids[ii][1])) + 0.118*math.cos(5*(centroid[1] - centroids[ii][1])) # this is the conversion factor from degrees to meters at the centroid's latitude
            # dy_m = 111132.92 - 559.82*math.cos(2*(centroid[1] - centroids[ii][1])) + 1.175*math.cos(4*(centroid[1] - centroids[ii][1])) - 0.0023*math.cos(6*(centroid[1] -centroids[ii][1]))
            dx_d = (centroid[0] - centroids[ii][0])*dx_m
            dy_d = (centroid[1] - centroids[ii][1])*dy_m
            tolerance_m = 5.0 # tolerance in meters of distance between centroids to consider them the same building
            if math.sqrt(dx_d*dx_d + dy_d*dy_d) < tolerance_m:
                if (centroid_to_features[str(centroids[ii])]["buildingheight"] != "NA"):
                    inventory.inventory[assetid].features["buildingheight"] = centroid_to_features[str(centroids[ii])]["buildingheight"]
                elif not flag_NA:
                    flag_NA = True
                if inventory.inventory[assetid].features.get("numstories", "NA") == "NA" and ("numstories" in centroid_to_features[str(centroids[ii])].keys()):
                    inventory.inventory[assetid].features["numstories"] = centroid_to_features[str(centroids[ii])]["numstories"]
            elif not flag_NA: 
                flag_NA = True
    for assetid in inventory.inventory.keys():
        if inventory.inventory[assetid].features.get("buildingheight", "NA") == "NA":
            flag_NA = True
            break
    if len(inventory.inventory) == 0:
        print("No buildings found in inventory...")
        flag_NA = True
    return flag_NA # indicate whether or not any combining was NOT done for building heights (i.e. whether or not there are still missing building heights)
   
def buildingheight_from_numstories(inventory):
    '''
    For use on OSM footprints, as they contain numstories as a key.
    Infer building height from number of stories, if building height is missing.
    Parameters:
        inventory: the inventory to check
    '''
    default_stories = 1 # default number of stories if not specified
    height_of_story = 3.0 # meters, naive approximation, does not account for roof height
    for assetid in inventory.inventory.keys():
        if "buildingheight" in inventory.inventory[assetid].features.keys() and "numstories" in inventory.inventory[assetid].features.keys():
            if inventory.inventory[assetid].features.get("buildingheight", "NA") == "NA" and inventory.inventory[assetid].features.get("numstories", "NA") != "NA":
                    inventory.inventory[assetid].features["buildingheight"] = height_of_story*inventory.inventory[assetid].features["numstories"] # naive approximation, 3 meters per story, does not account for roof heights
    return inventory
    
def inventory_miss_and_hit(inventory, key="buildingheight"):
    '''
    Check the number of missing and hit values for a given key in the inventory.
    Parameters:
        inventory: the inventory to check
        key: the key to check for missing values
    '''
    miss_count = 0
    hit_count = 0
    for assetid in inventory.inventory.keys():
        if inventory.inventory[assetid].features.get(key, "NA") == "NA":
            miss_count += 1
        else:
            hit_count += 1
    return miss_count, hit_count                    
    
def scrape_footprints(scraper, importer, region_boundary_object):
    print(f"Using {scraper} ...")
    _class = importer.get_class(scraper)
    _scraper = _class({"length": "m"})
    inventory = _scraper.get_footprints(region_boundary_object)
    return inventory

def get_brails(bbox, inventory_filename="CelerisInit/building_inventory.geojson"):
    """
    Use BRAILS package to access public building inventory databases

    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
    """
    importer = Importer()
    region_boundary_class = importer.get_class("RegionBoundary")
    region_boundary_object = region_boundary_class({"type": "locationPolygon", "data":bbox})
    
    print("Trying MS_FootprintScraper ...")
    ms_inventory = scrape_footprints("MS_FootprintScraper", importer, region_boundary_object)
    ms_inventory = buildingheight_from_numstories(ms_inventory) # Many global locations have numstories, but not buildingheight. Proactively infer buildingheight for more robust workflow when MS and USA have no buildings at all (e.g., for Okinawa, Japan)
    ms_miss_count, ms_hit_count = inventory_miss_and_hit(ms_inventory, key="buildingheight")

    flag_NA = False # Check if we need to fill in missing data with another scraper
    for assetid in ms_inventory.inventory.keys():
        if ms_inventory.inventory[assetid].features.get("buildingheight", "NA") == "NA":
            flag_NA = True
            break
    if len(ms_inventory.inventory) == 0:
        print("No buildings found in inventory...")
        flag_NA = True
            
    # Missing data, try to fill in with OSM Footprints 
    if flag_NA:
        print("Missing data in inventory ...")
        print("Trying OSM_FootprintScraper ...")
        osm_inventory = scrape_footprints("OSM_FootprintScraper", importer, region_boundary_object)
        osm_inventory = buildingheight_from_numstories(osm_inventory) # Many global locations have numstories, but not buildingheight. Proactively infer buildingheight for more robust workflow when MS and USA have no buildings at all (e.g., for Okinawa, Japan)
        try:
            flag_NA = combine_inventories(ms_inventory, osm_inventory) # combine the two inventories, filling in missing data from OSM
        except:
            print("Error combining OSM inventory with MS inventory")
    
    # Still missing data, try to fill in with USA Footprints
    if flag_NA:
        print("Missing data in inventory ...")
        print("Trying USA_FootprintsScraper ...")
        usa_inventory = scrape_footprints("USA_FootprintScraper", importer, region_boundary_object)
        usa_inventory = buildingheight_from_numstories(usa_inventory) # Many global locations have numstories, but not buildingheight. Proactively infer buildingheight for more robust workflow when MS and OSM have no buildings at all (e.g., for Okinawa, Japan)
        try:
            flag_NA = combine_inventories(ms_inventory, usa_inventory) # combine the two inventories, filling in missing data from USA
        except:
            print("Error combining USA inventory with MS inventory")
    
    # Check which scraper inventory has less missing data
    reference_count = 0 # count statistic to determine whether or not KNN imputation will give meaningful results
    if flag_NA:
        osm_miss_count, osm_hit_count = inventory_miss_and_hit(osm_inventory, key="buildingheight")
        usa_miss_count, usa_hit_count = inventory_miss_and_hit(usa_inventory, key="buildingheight")
        print("MS Inventory: ", ms_miss_count, "missing, ", ms_hit_count, "hit")
        print("OSM Inventory: ", osm_miss_count, "missing, ", osm_hit_count, "hit")
        print("USA Inventory: ", usa_miss_count, "missing, ", usa_hit_count, "hit")
        
        try:
            combine_inventories(osm_inventory, ms_inventory) # combine the two inventories, filling in missing data from MS
        except:
            print("Error combining MS inventory with OSM inventory")
        try:
            combine_inventories(osm_inventory, usa_inventory) # combine the two inventories, filling in missing data from USA
        except:
            print("Error combining USA inventory with OSM inventory")
            
        try:
            combine_inventories(usa_inventory, ms_inventory) # combine the two inventories, filling in missing data from MS
        except:
            print('Error combining MS inventory with USA inventory')
        try:
            combine_inventories(usa_inventory, osm_inventory) # combine the two inventories, filling in missing data from OSM
        except:
            print('Error combining OSM inventory with USA inventory')
        
        ms_merged_miss_count, ms_merged_hit_count = inventory_miss_and_hit(ms_inventory, key="buildingheight")
        osm_merged_miss_count, osm_merged_hit_count = inventory_miss_and_hit(osm_inventory, key="buildingheight")
        usa_merged_miss_count, usa_merged_hit_count = inventory_miss_and_hit(usa_inventory, key="buildingheight")
        print("MS Merged Inventory: ", ms_merged_miss_count, "missing, ", ms_merged_hit_count, "hit")
        print("OSM Merged Inventory: ", osm_merged_miss_count, "missing, ", osm_merged_hit_count, "hit")
        print("USA Merged Inventory: ", usa_merged_miss_count, "missing, ", usa_merged_hit_count, "hit")
        
        if (ms_merged_hit_count > osm_merged_hit_count and ms_merged_hit_count > usa_merged_hit_count):
            print("Using MS Merged Inventory")
            inventory = ms_inventory  
            reference_count = ms_merged_hit_count
        elif (osm_merged_hit_count > ms_merged_hit_count and osm_merged_hit_count > usa_merged_hit_count):
            print("Using OSM Merged Inventory")
            inventory = osm_inventory
            reference_count = osm_merged_hit_count
        elif (usa_merged_hit_count > ms_merged_hit_count and usa_merged_hit_count > osm_merged_hit_count):
            print("Using USA Merged Inventory")
            inventory = usa_inventory
            reference_count = usa_merged_hit_count
        else:
            print("Using MS Merged Inventory as Default...")
            inventory = ms_inventory
            reference_count = ms_merged_hit_count
    else:
        inventory = ms_inventory # if no missing data, use MS inventory
        reference_count = ms_hit_count
    
    filled_inventory = inventory
    guess_count = 0
    story_count = 0
    imp_miss_count = None
    imp_hit_count = 0
    if flag_NA and len(inventory.inventory) > 0 and reference_count > len(inventory.inventory)/2:
        knn_imputer_class = importer.get_class("KnnImputer")
        nbldg_per_cluster = min(len(inventory.inventory)/4, 500) # number of buildings per cluster, can be adjusted based on the density of the area
        imputer = knn_imputer_class(input_inventory=inventory, nbldg_per_cluster = nbldg_per_cluster, seed=42) # What is n_possible_worlds? What is gen_method? Documentation is out of date?
        filled_inventory = imputer.impute() 
        imp_miss_count, imp_hit_count = inventory_miss_and_hit(filled_inventory, key="buildingheight")
        print("Imputed Inventory: ", imp_miss_count, "missing, ", ms_hit_count, "hit")

    if not imp_miss_count or imp_miss_count > 0:
        for assetid in filled_inventory.inventory.keys():
            if filled_inventory.inventory[assetid].features.get("buildingheight", "NA") == "NA":
                if filled_inventory.inventory[assetid].features.get("numstories", "NA") == "NA":
                    filled_inventory.inventory[assetid].features["numstories"] = 1 # worst case guess
                    filled_inventory.inventory[assetid].features["buildingheight"] = 3 # worst case guess
                    guess_count += 1
                else:
                    filled_inventory.inventory[assetid].features["buildingheight"] = 3*filled_inventory.inventory[assetid].features["numstories"] # naive approximation, 3 meters per story, does not account for roof height
                    story_count += 1
    total = len(filled_inventory.inventory)
    print(f"[Imputation report] Original Height: {100*reference_count/total}%, KNN Imputed: {100*imp_hit_count/total}%, Estimated from stories: {100*story_count/total}%, Complete guess: {100*guess_count/total}%")
    # _ = filled_inventory.write_to_geojson(inventory_filename) # TODO This prints the entire inventory, not sure how to suppress the print
    return filled_inventory.inventory


def download_sea_anomaly(bbox, date): # difficult to query reliably, data is not great, so not used
    """
    Download sea anomaly data for a given date.
    
    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
        date: tuple of (year, month, day)
    """
    erddap_file_url = f"https://coastwatch.noaa.gov/erddap/files/noaacwBLENDEDsshDaily/{date[0]}/rads_global_nrt_sla_{date[0]}{str(date[1]).zfill(2)}{date[2]-1}_{date[0]}{str(date[1]).zfill(2)}{date[2]}_001.nc"
    file_name = f"./netCDF_data/sla_{date[0]}{str(date[1]).zfill(2)}{date[2]}.nc"
    response = requests.get(erddap_file_url)
    response.raise_for_status()  # Raise error for bad status

    with open(file_name, 'wb') as f:
        f.write(response.content)
    print(f"Downloaded sea anomaly data")

def get_sea_anomaly(bbox, date):
    """
    Get sea anomaly level at region specified by bbox for a given date.
    The average is taken at a 4x4 kernel to get a single sea level. (kernel size chosen semi-arbitrarily, so that it's 1 degree by 1 degree)
    More sophisticated strategies (time series analysis?) could be taken later.

    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
        date: tuple of (year, month, day)
    """
    file_name = f"./netCDF_data/sla_{date[0]}{str(date[1]).zfill(2)}{date[2]}.nc"
    file_id = Dataset(file_name) # dict_keys(['crs', 'longitude', 'latitude', 'lon_bnds', 'lat_bnds', 'time', 'time_bnds', 'sla', 'ugos', 'vgos'])

    # DEBUG = np.array(file_id.variables['sla'][0,:,:]) # docs say dimensions are always [time][latitude][longitude], but in this case time is always 0 as it is only taken once a day
    # DEBUG[DEBUG==-32767] = np.nan  
    # visualize(DEBUG)
    
    # Perhaps this could be done more optimally
    lng_begin = 0
    for i in range(len(file_id.variables['longitude'])): 
        if file_id.variables['longitude'][lng_begin] >= bbox[0]: 
            lng_begin-=2
            break
        lng_begin+=1
    lat_begin = 0
    for i in range(len(file_id.variables['latitude'])): 
        if file_id.variables['latitude'][lat_begin] >= bbox[1]: 
            lat_begin-=2
            break
        lat_begin+=1
    lng_end = 0
    for i in range(len(file_id.variables['longitude'])): 
        if file_id.variables['longitude'][lng_end] >= bbox[2]: 
            lng_end+=2
            break
        lng_end+=1
    lat_end = 0
    for i in range(len(file_id.variables['latitude'])): 
        if file_id.variables['latitude'][lat_end] >= bbox[3]: 
            lat_end+=2
            break
        lat_end+=1

    sealevels = []
    for lat in range(lat_begin, lat_end):
        for lng in range(lng_begin, lng_end):
            coord = (file_id.variables['latitude'][lat], file_id.variables['longitude'][lng])
            if file_id.variables['sla'][0,lat,lng] != "--":
                sealevels.append(file_id.variables['sla'][0,lat,lng])
    if not sealevels:
        print("No Sea Anomaly Data At This Location")
        return 0
    return sum(sealevels)/len(sealevels)

def visualize(bathy_array=None, building_mask=None, filename="./CelerisInit/overlay.png", dx=1, dy=1, bbox=None, visualize_buildings=True):
    """
    Plot resulting topobathy for manual visual analysis, save overlay image for Celeris
    Parameters:
        bathy_array: array of bathymetry values
        filename: file path for overlay png
        dx: degree width of cell
        dy: degree height of cell
    """
    dpi = 300  # dots per inch for high resolution
    height, width = bathy_array.shape[:2]
    fig, axes = plt.subplots(1, 1, figsize=(width / dpi, height / dpi), dpi=dpi)
    dx_m = 111412.84*math.cos(dx) - 93.5*math.cos(3*dx) + 0.118*math.cos(5*dx)
    dy_m = 111132.92 - 559.82*math.cos(2*dx) + 1.175*math.cos(4*dx) - 0.0023*math.cos(6*dx)
    hillshade = bathy_array.copy()
    ls = clr.LightSource(azdeg=315, altdeg=45)
    if bbox:
        axes.set_xlim(0, bathy_array.shape[0])
        axes.set_ylim(0, bathy_array.shape[1])
        axes.set_xticks([0, 0.25 * bathy_array.shape[0], 0.5 * bathy_array.shape[0], 0.75 * bathy_array.shape[0], bathy_array.shape[0]])
        axes.set_yticks([0, 0.25 * bathy_array.shape[1], 0.5 * bathy_array.shape[1], 0.75 * bathy_array.shape[1], bathy_array.shape[1]])
        axes.set_xticklabels([f"{x:.4f}" for x in [bbox[0], (bbox[0] + (bbox[2] - bbox[0]) / 4), (bbox[0] + (bbox[2] - bbox[0]) / 2), (bbox[0] + 3 * (bbox[2] - bbox[0]) / 4), (bbox[2])]], rotation=30)
        axes.set_yticklabels([f"{y:.4f}" for y in [bbox[1], (bbox[1] + (bbox[3] - bbox[1]) / 4), (bbox[1] + (bbox[3] - bbox[1]) / 2), (bbox[1] + 3 * (bbox[3] - bbox[1]) / 4), (bbox[3])]], rotation=30)
        axes.tick_params(axis='both', direction='out', length=4, width=1, colors='black', labelsize=8)
        axes.set_xlabel('Longitude (degrees)', fontsize=8)
        axes.set_ylabel('Latitude (degrees)', fontsize=8)
    else:
        axes.axis('off')
    # mask = (hillshade >= 0)
    # normalize = np.empty_like(hillshade)
    # normalize[mask] = np.sqrt(hillshade[mask])
    # normalize[~mask] = hillshade[~mask]
    axes.imshow(ls.shade(np.flip(hillshade, axis=0), vert_exag=10, dx=dx_m, dy=dy_m, cmap=plt.cm.gist_earth, norm=clr.TwoSlopeNorm(vcenter=0), blend_mode="hsv"))
    
    
    if visualize_buildings:
        rgba = np.zeros((*hillshade.shape, 4))  # initialize transparent
        rgba[building_mask, 0] = 0.5
        rgba[building_mask, 1] = 0.5
        rgba[building_mask, 2] = 0.5
        rgba[building_mask, 3] = 0.8
        axes.imshow(np.flip(rgba, axis=0), interpolation=None)

    # save as correct (higher) resolution png
    # dpi = 300
    # fig = plt.figure(figsize = (width / dpi, height / dpi), dpi=dpi)
    # ax = fig.add_axes([0, 0, 1, 1])
    # ax.imshow(ls.shade(hillshade, vert_exag=10, dx=dx_m, dy=dy_m, cmap=plt.cm.gist_earth, norm=clr.TwoSlopeNorm(vcenter=0), blend_mode="hsv"))
    # ax.imshow(rgba, interpolation=None)
    # ax.axis('off')

    # Save the plot to a file
    plt.savefig(filename, format='png', transparent=True, bbox_inches='tight', pad_inches=0)
    print(f"Plot saved to {filename}")
    plt.show()
    plt.close(fig)
    # plt.show()
    
def merge(dem_file, inventory, bbox, resolution_factor, scale_factor=2):
    """
    Merge the bathymetry-topography and building inventory into a single topobathy array.
    """

    with Image.open(dem_file) as img:
        img = img.resize((int(scale_factor * img.size[0]), int(scale_factor * img.size[1])), Image.LANCZOS)
        grayscale_img = img.convert("F")
        mask_image = Image.new('F', grayscale_img.size)
        for assetid in inventory.keys():
            coords = inventory[assetid].coordinates
            coords = [((coord[0] - bbox[0]) * resolution_factor * scale_factor,
                       -1 * (coord[1] - bbox[3]) * resolution_factor * scale_factor)
                      for coord in coords]
            draw = ImageDraw.Draw(grayscale_img)
            mask_draw = ImageDraw.Draw(mask_image)
            groundlevel = max([grayscale_img.getpixel(tuple(xy))
                               if 0 <= xy[0] < grayscale_img.size[0] and 0 <= xy[1] < grayscale_img.size[1]
                               else 0 for xy in coords])
            buildingheight = inventory[assetid].features.get("buildingheight", "NA")
            if buildingheight == "NA":
                buildingheight = -9999 # fallback value
            draw.polygon(coords, fill=buildingheight + groundlevel, outline=None)
            mask_draw.polygon(coords, fill=1, outline=None)
        bathy_array = np.array(grayscale_img)
        building_mask = (np.array(mask_image) > 0)
        print(f"Fetched topobathy array. Width: {bathy_array.shape[1]}, Height: {bathy_array.shape[0]}")

    return bathy_array, building_mask

def geocode_location(location_text):
    geolocator = Nominatim(user_agent="bbox_locator")
    location = geolocator.geocode(location_text)
    if not location:
        raise ValueError(f"Could not geocode location: '{location_text}'")
    return location.latitude, location.longitude

def create_bbox(lat, lon, buffer_deg=0.01):
    # buffer_deg is in degrees (e.g., ~1.1 km at equator)
    return (
        lon - buffer_deg,  # xmin
        lat - buffer_deg,  # ymin
        lon + buffer_deg,  # xmax
        lat + buffer_deg   # ymax
    )
    
def calc_base_depth(row):
    negative_values = row[row < 0]
    negative_values = negative_values[~np.isnan(negative_values)]
    if negative_values.size > 0:
        # remove NaN values
        base_depth = abs(np.mean(negative_values))
    else:
        base_depth = 1.0
    return base_depth
    
def main():
    __location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
    parser = argparse.ArgumentParser(
                        description="Download DEM, retrieve building inventory, and generate topobathy inputs for Celeris."
                             "Use --bbox to specify a bounding box or --address to geocode an address. "
                             "If using --address, specify a buffer in degrees with --buffer. "
                             "Switch between modes with --mode. ['bbox', 'address']"
                             "Example: --bbox -122.34053007546347 37.8992412074125 -122.32314730065123 37.91514928711621 "
                             "or --address 'Richmond Field Station, Richmond, CA' --buffer 0.01"
                             "resolution_factor is the number of pixels per degree, default is 37000 for approximately 3 meter pixels."
                             "dem_file is the path to save the DEM, default is './ArcGIS_outputs/global_dem.tiff'. "
                             "scale_factor is the resampling scale factor, default is 2 for doubling the resolution."
                             "Example usage: python main.py --mode address --address 'Richmond Field Station, Richmond, CA' --buffer 0.01 --scale_factor 2"
                             "Example usage: python main.py --mode bbox --bbox -122.34053007546347 37.8992412074125 -122.32314730065123 37.91514928711621 --scale_factor 2"
                             )
    parser.add_argument("--bbox", type=float, nargs=4, default=[-122.34053007546347, 37.8992412074125, -122.32314730065123, 37.91514928711621],
                        help="Bounding box as xmin ymin xmax ymax (WGS84)")
    parser.add_argument("-r", "--resolution_factor", type=int, default=37000,
                        help="Resolution factor (pixels per degree)")
    parser.add_argument("--resolution", type=float, default=3.0, 
                        help="Approximate resolution in meters per pixel to request from the NOAA bathymetry API. This is used to calculate the resolution factor.")
    parser.add_argument("-s", "--scale_factor", type=float, default=2,
                        help="Resampling scale factor")
    parser.add_argument("-a", "--address", type=str, default="Richmond Field Station, Richmond, CA",
                        help="Address to use for bounding box geocoding. Only used if --mode is 'address'.")
    parser.add_argument("-b", "--buffer", type=float, default=0.01,
                        help="Buffer in degrees to expand the bounding box around the geocoded address centroid. Only used if --mode is 'address'.")
    parser.add_argument("-m", "--mode", type=str, default="bbox", required=True, # should this be required when there's already a default value?
                        choices=["bbox", "address"],
                        help="Mode of operation ['bbox', 'address']: 'bbox' for using bbox directly, (e.g. --mode bbox --bbox -122.34053007546347 37.8992412074125 -122.32314730065123 37.91514928711621), 'address' for geocoding an address to get bbox (e.g., --mode address --address 'Richmond Field Station, Richmond, CA' --buffer 0.01).")
    parser.add_argument("--offset", nargs=2, type=float, default=[0.0, 0.0],
                        help="Offset longitude and latitude in degrees to apply to the bounding box. E.g., --offset 0.01 -0.005")
    parser.add_argument("--disable_brails", action='store_true', default=False,
                        help="Disable BRAILS building inventory retrieval. If set, no buildings will be merged onto the bathymetry.")
    # Add an argument for the output directory
    parser.add_argument("--output_directory", type=str, default="CelerisInit", help="Output directory for the config file.")
    dem_directory_default = "ArcGIS_outputs"
    dem_filename_default = os.path.join(__location__, dem_directory_default, "global_dem.tiff")
    parser.add_argument("--dem_file", type=str, default=dem_filename_default,
                        help="Filename for the retrieved DEM")
    # Add a useful help tip for incorrect usage
    args = parser.parse_args()

    if args.mode == "address":
        lat, lon = geocode_location(args.address)
        bbox = create_bbox(lat, lon, args.buffer)
    elif args.mode == "bbox":
        bbox = tuple(args.bbox)
        if bbox[0] > bbox[2]:
            bbox = (bbox[2], bbox[1], bbox[0], bbox[3])  # Ensure xmin < xmax
        if bbox[1] > bbox[3]:
            bbox = (bbox[0], bbox[3], bbox[2], bbox[1])
        if bbox[0] == bbox[2] or bbox[1] == bbox[3]:
            raise ValueError("Invalid bounding box: xmin must be less than xmax and ymin must be less than ymax.")
    bbox = (bbox[0] + args.offset[0], bbox[1] + args.offset[1], bbox[2] + args.offset[0], bbox[3] + args.offset[1])
    print(f"Using bounding box: {bbox}")
        
    resolution_factor = args.resolution_factor
    dem_file = args.dem_file
    scale_factor = args.scale_factor

    # Time for sea anomaly altimetry data. Tuple of (year, month, day)
    # date = (2025, 6, 11) # TODO sea anomaly data was problematic

    output_directory = args.output_directory
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)
        print(f"Output directory: {output_directory}")
        
    USE_PROCESSES = True # Set to True to use processes, False to execute sequentially in the main thread

    if not os.path.exists("./ArcGIS_outputs"):
        os.makedirs("./ArcGIS_outputs")
    if USE_PROCESSES:
        dem_p = Process(target=get_dem, kwargs={
            "bbox": bbox,
            "out_path": dem_file,
            "resolution_factor": resolution_factor
        })
        dem_p.start()
    else:
        get_dem(bbox=bbox, out_path=dem_file, resolution_factor=resolution_factor)
    
    # Retrieve sea anomaly altimetry raster data and save as .nc file
    # if USE_PROCESSES:
    #     sea_p = Process(target=download_sea_anomaly, kwargs={
    #         "bbox": bbox,
    #         "date": date,
    #         })
    #     sea_p.start()
    # else:
    #     download_sea_anomaly(bbox=bbox, date=date)

    if not args.disable_brails:
        print("Retrieving building inventory using BRAILS...")
        if not os.path.exists("./mergebuffer"):
            os.makedirs("./mergebuffer")
        inventory_filename = os.path.join(__location__, "mergebuffer", "building_inventory.geojson")
        inventory = get_brails((bbox[0], bbox[1], bbox[2], bbox[1], bbox[2], bbox[3], bbox[0], bbox[3]), inventory_filename)
    else:
        print("BRAILS building inventory retrieval disabled. No buildings will be merged onto the bathymetry.")
        # Set inventory to an empty dict to avoid errors in merge
        inventory = {}
        
    if USE_PROCESSES:
        dem_p.join()
        if dem_p.exitcode > 0:
            raise ValueError(f'GET child process exited with code {dem_p.exitcode}')

    print("Merge DEM and Inventory...")
    bathy_array, building_mask = merge(dem_file, inventory, bbox, resolution_factor, scale_factor)
    print("Merged DEM and Inventory")

    dx = Geodesic.WGS84.Inverse(bbox[1], bbox[0], bbox[1], bbox[2], outmask=1025)['s12'] / bathy_array.shape[1]
    dy = Geodesic.WGS84.Inverse(bbox[1], bbox[0], bbox[3], bbox[0], outmask=1025)['s12'] / bathy_array.shape[0]

    print("Plotting Topobathy Array")
    bathy_filename = os.path.join(os.path.dirname(__file__), output_directory, "overlay.png")
    vis_p = Process(target=visualize, kwargs={"bathy_array": bathy_array, "filename": bathy_filename, "building_mask":building_mask, "dx": dx, "dy": dy, "bbox": bbox, "visualize_buildings": True}, daemon=True)
    vis_p.start()

    output_bathy_filename = os.path.join(__location__, output_directory, "bathy.txt")
    np.savetxt(output_bathy_filename, np.flipud(bathy_array), delimiter=' ', newline='\n')
    print("bathy.txt saved")

    # Whichever boundary is the deepest (i.e., the ocean) will be where waves are inflowing
    north_depth = np.mean(bathy_array[0, :])
    south_depth = np.mean(bathy_array[-1, :])
    west_depth = np.mean(bathy_array[:, 0])
    east_depth = np.mean(bathy_array[:, -1])
    north_boundary_type = 0 # solid wall
    south_boundary_type = 0 # solid wall
    west_boundary_type = 0 # solid wall
    east_boundary_type = 0 # solid wall
    if north_depth < south_depth and north_depth < west_depth and north_depth < east_depth:
        north_boundary_type = 2 # incoming wave boundary condition
        base_depth = calc_base_depth(bathy_array[0, :])
        wave_direction = 3 * math.pi / 2
    elif south_depth < north_depth and south_depth < west_depth and south_depth < east_depth:
        south_boundary_type = 2 # incoming wave boundary condition
        base_depth = calc_base_depth(bathy_array[-1, :])
        wave_direction = math.pi / 2
    elif west_depth < north_depth and west_depth < south_depth and west_depth < east_depth:
        west_boundary_type = 2 # incoming wave boundary condition
        base_depth = calc_base_depth(bathy_array[:, 0])
        wave_direction = 0.0
    elif east_depth < north_depth and east_depth < south_depth and east_depth < west_depth:
        east_boundary_type = 2 # incoming wave boundary condition
        base_depth = calc_base_depth(bathy_array[:, -1])
        wave_direction = math.pi
    else:
        west_boundary_type = 2 # default to west boundary condition if all depths are equal
        base_depth = calc_base_depth(bathy_array[:, 0])
        wave_direction = 0.0
    config_params = {
        "north_boundary_type": north_boundary_type,  # 0=solid wall, 1=sponge layer, 2=waves loaded from file
        "east_boundary_type": east_boundary_type,  # 0=solid wall, 1=sponge layer, 2=waves loaded from file
        "west_boundary_type": west_boundary_type,  # 0=solid wall, 1=sponge layer, 2=waves loaded from file
        "south_boundary_type": south_boundary_type,  # 0=solid wall, 1=sponge layer, 2=waves loaded from file
        "base_depth": base_depth,  # depth of the ocean
    }
    
    numwaves = 1
    wave_amplitude = 10.0
    wave_period = 10.0
    wave_phase = 1.0
    amplitude, period, direction, phase = ([wave_amplitude for _ in range(numwaves)],
                                           [wave_period for _ in range(numwaves)],
                                           [wave_direction for _ in range(numwaves)],
                                           [wave_phase for _ in range(numwaves)])
    config_params["WaveType"] = -1 # -1 = file (waves.txt), 0, 1, or 2 = sine wave, 3 = solitary wave 
    
    
    config_params["lon_LL"] = bbox[0]
    config_params["lat_LL"] = bbox[1]
    config_params["lon_UR"] = bbox[2]
    config_params["lat_UR"] = bbox[3]

    config_params["width"] = bathy_array.shape[1]
    config_params["height"] = bathy_array.shape[0]
    config_params["dx"] = dx
    config_params["dy"] = dy
    # if (USE_PROCESSES):
    #     sea_p.join()
    # config_params["seaLevel"] = get_sea_anomaly(bbox, date)
    output_config_filename = os.path.join(__location__, output_directory, "config.json")
    create_config(output_config_filename, **config_params)
    print("config.json saved")

    output_waves_filename = os.path.join(__location__, output_directory, "waves.txt")
    create_waves(output_waves_filename, numwaves, amplitude, period, direction, phase)
    print("waves.txt saved")

    vis_p.join()
    print("Plot Closed!")

if __name__ == "__main__":
    main()