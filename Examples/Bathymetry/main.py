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
import_or_install('requests')
import_or_install('geographiclib')
import_or_install('geopy')
import_or_install('brails')

# from vincenty import vincenty # more accurate than methods like the Haverside function, that assume a 'spherical earth'/'great circle distance'
import argparse
from multiprocessing import Process
import requests
import os
from PIL import Image, ImageDraw, ImagePath
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as clr
import math
from geographiclib.geodesic import Geodesic
from geopy.geocoders import Nominatim
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
        # os.remove("./mergebuffer/left.tiff") # keep for now to debug
        right_img = Image.open("./mergebuffer/right.tiff")
        # os.remove("./mergebuffer/right.tiff") # keep for now to debug
        if left_img.height != right_img.height:
            raise ValueError("DEBUG!")

        new_width = left_img.width + right_img.width
        new_image = Image.new("F", (new_width, left_img.height))
        new_image.paste(left_img, (0, 0))
        new_image.paste(right_img, (left_img.width, 0))
        new_image.save(out_path)

    else:
        _download_dem(bbox, out_path, resolution_factor = resolution_factor, size = size, pixel_type=pixel_type, interpolation = interpolation) # need to set size

def get_brails(bbox):
    """
    Use BRAILS package to access public building inventory databases

    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
    """
    importer = Importer()
    region_boundary_class = importer.get_class("RegionBoundary")
    region_boundary_object = region_boundary_class({"type": "locationPolygon", "data":bbox})

    # print("Using OSM_FootprintsScraper ...")
    # osm_class = importer.get_class("OSM_FootprintScraper")
    # osm_scraper = osm_class({"length": "ft"})
    # osm_inventory = osm_scraper.get_footprints(region_boundary_object)

    # print("Using Microsoft Footprint Database ...")
    # ms_class = importer.get_class("MS_FootprintScraper")
    # ms_scraper = ms_class({"length": "ft"})
    # ms_inventory = ms_scraper.get_footprints(region_boundary_object)

    print("Using USA_FootprintsScraper ...")
    usa_class = importer.get_class("USA_FootprintScraper")
    usa_scraper = usa_class({"length": "ft"})
    usa_inventory = usa_scraper.get_footprints(region_boundary_object)
    if len(usa_inventory.inventory) > 0: # known to throw keyerror, not sure if it will happen when there are no missing records to impute TODO
        knn_imputer_class = importer.get_class("KnnImputer")
        nbldg_per_cluster = min(len(usa_inventory.inventory)/4, 500) # number of buildings per cluster, can be adjusted based on the density of the area
        imputer = knn_imputer_class(input_inventory=usa_inventory, nbldg_per_cluster = nbldg_per_cluster, seed=42) # What is n_possible_worlds? What is gen_method? Documentation is out of date?
        filled_inventory = imputer.impute() 
    else:
        filled_inventory = usa_inventory
    return filled_inventory.inventory

def visualize(bathy_array=None, filename="./CelerisInit/bathy.png"):
    """
    Plot resulting topobathy for manual visual analysis

    Parameters:
        bbox: tuple of (xmin, ymin, xmax, ymax) in WGS84
    """
    plt.figure(figsize=(8, 6))
    plt.imshow(bathy_array, cmap='viridis', norm=clr.SymLogNorm(linthresh = 1), origin='upper')
    plt.colorbar(label='Pixel Value')
    plt.title('2D Array')
    plt.xlabel('Column Index')
    plt.ylabel('Row Index')
    plt.tight_layout()
    # visualize footprints in plot
    # for assetid in inventory.keys():
    #     coords = inventory[assetid].coordinates
    #     x, y = zip(*coords)
    #     x = [(i-bbox[0])*resolution_factor for i in x]
    #     y = [-1*(i-bbox[3])*resolution_factor for i in y]
    #     plt.fill(x, y)
    plt.show()
    # Save the plot to a file
    plt.savefig(filename)
    print(f"Plot saved to {filename}")
    
def merge(dem_file, inventory, bbox, resolution_factor, scale_factor=2):
    """
    Merge the bathymetry-topography and building inventory into a single topobathy array.
    """

    with Image.open(dem_file) as img:
        img = img.resize((int(scale_factor * img.size[0]), int(scale_factor * img.size[1])), Image.LANCZOS)
        grayscale_img = img.convert("F")

        for assetid in inventory.keys():
            coords = inventory[assetid].coordinates
            coords = [((coord[0] - bbox[0]) * resolution_factor * scale_factor,
                       -1 * (coord[1] - bbox[3]) * resolution_factor * scale_factor)
                      for coord in coords]
            draw = ImageDraw.Draw(grayscale_img)

            groundlevel = max([grayscale_img.getpixel(tuple(xy))
                               if 0 <= xy[0] < grayscale_img.size[0] and 0 <= xy[1] < grayscale_img.size[1]
                               else 0 for xy in coords])
            buildingheight = inventory[assetid].features.get("buildingheight", "NA")
            if buildingheight == "NA":
                buildingheight = -9999
            draw.polygon(coords, fill=buildingheight + groundlevel, outline=None)

        bathy_array = np.array(grayscale_img)
        print(f"Fetched topobathy array. Width: {bathy_array.shape[1]}, Height: {bathy_array.shape[0]}")

    return bathy_array

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
    parser.add_argument("-s", "--scale_factor", type=float, default=2,
                        help="Resampling scale factor")
    parser.add_argument("-a", "--address", type=str, default="Richmond Field Station, Richmond, CA",
                        help="Address to use for bounding box geocoding. Only used if --mode is 'address'.")
    parser.add_argument("-b", "--buffer", type=float, default=0.01,
                        help="Buffer in degrees to expand the bounding box around the geocoded address centroid. Only used if --mode is 'address'.")
    parser.add_argument("-m", "--mode", type=str, default="bbox", required=True,
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
    bbox = (bbox[0] + args.offset[0], bbox[1] + args.offset[1], bbox[2] + args.offset[0], bbox[3] + args.offset[1])
    print(f"Using bounding box: {bbox}")
        
    resolution_factor = args.resolution_factor
    dem_file = args.dem_file
    scale_factor = args.scale_factor

    config_params = {
        "south_boundary_type": 2
    }

    numwaves = 1
    amplitude, period, direction, phase = ([10 for _ in range(numwaves)],
                                           [5 for _ in range(numwaves)],
                                           [math.pi / 2 for _ in range(numwaves)],
                                           [1 for _ in range(numwaves)])
    
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
    
    if not args.disable_brails:
        print("Retrieving building inventory using BRAILS...")
        if not os.path.exists("./mergebuffer"):
            os.makedirs("./mergebuffer")
        inventory = get_brails((bbox[0], bbox[1], bbox[2], bbox[1], bbox[2], bbox[3], bbox[0], bbox[3]))
    else:
        print("BRAILS building inventory retrieval disabled. No buildings will be merged onto the bathymetry.")
        # Set inventory to an empty dict to avoid errors in merge
        inventory = {}
        
    if USE_PROCESSES:
        dem_p.join()
        if dem_p.exitcode > 0:
            raise ValueError(f'GET child process exited with code {dem_p.exitcode}')

    print("Merge DEM and Inventory...")
    bathy_array = merge(dem_file, inventory, bbox, resolution_factor, scale_factor)
    print("Merged DEM and Inventory")

    print("Plotting Topobathy Array")
    bathy_filename = os.path.join(os.path.dirname(__file__), output_directory, "bathy.png")
    vis_p = Process(target=visualize, kwargs={"bathy_array": bathy_array, "filename": bathy_filename}, daemon=True)
    vis_p.start()

    output_bathy_filename = os.path.join(__location__, output_directory, "bathy.txt")
    np.savetxt(output_bathy_filename, np.flipud(bathy_array), delimiter=' ', newline='\n')
    print("bathy.txt saved")

    config_params["width"] = bathy_array.shape[1]
    config_params["height"] = bathy_array.shape[0]
    config_params["dx"] = Geodesic.WGS84.Inverse(bbox[1], bbox[0], bbox[1], bbox[2], outmask=1025)['s12'] / bathy_array.shape[1]
    config_params["dy"] = Geodesic.WGS84.Inverse(bbox[1], bbox[0], bbox[3], bbox[0], outmask=1025)['s12'] / bathy_array.shape[0]
    output_config_filename = os.path.join(__location__, output_directory, "config.json")
    create_config(output_config_filename, **config_params)
    print("config.json saved")
    print(f"DEBUG! calculated (dx,dy):({config_params['dx']},{config_params['dy']})")

    output_waves_filename = os.path.join(__location__, output_directory, "waves.txt")
    create_waves(output_waves_filename, numwaves, amplitude, period, direction, phase)
    print("waves.txt saved")

    vis_p.join()
    print("Plot Closed!")

if __name__ == "__main__":
    main()