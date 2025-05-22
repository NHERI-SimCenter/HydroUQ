import pandas as pd
import numpy as np
from shapely import wkt
from shapely.geometry import box
import matplotlib.pyplot as plt
from shapely.affinity import translate

# === Parameters ===
csv_file = "Cube_Inventory.csv"  # Change this to your actual CSV path
pixel_size = 0.000009000009/1.99999999  # Degrees per pixel (adjust based on data resolution)

# === Step 1: Load data ===
df = pd.read_csv(csv_file)

# Fill missing number of floors with 1
df['NFloors'] = df['NFloors'].fillna(1).astype(int)

# Parse geometries
df['geometry'] = df['geometry'].apply(wkt.loads)

# === Step 2: Determine bounds ===
all_bounds = [geom.bounds for geom in df['geometry']]
minx = min(b[0] for b in all_bounds)
miny = min(b[1] for b in all_bounds)
maxx = max(b[2] for b in all_bounds)
maxy = max(b[3] for b in all_bounds)

width = int((maxx - minx) / pixel_size) + 1
height = int((maxy - miny) / pixel_size) + 1

print(f"Raster size: {width} x {height}")

# === Step 3: Create raster and fill ===
raster = np.zeros((height, width), dtype=np.uint8)

for _, row in df.iterrows():
    poly = row['geometry']
    floors = row['NFloors']

    # Translate polygon to raster origin
    translated = translate(poly, xoff=-minx, yoff=-miny)

    # Rasterize: loop over pixels covered by bounding box
    min_col = int(translated.bounds[0] / pixel_size)
    min_row = int(translated.bounds[1] / pixel_size)
    max_col = int(translated.bounds[2] / pixel_size)
    max_row = int(translated.bounds[3] / pixel_size)

    for i in range(min_row, max_row + 1):
        for j in range(min_col, max_col + 1):
            # Create pixel box
            pixel = box(j * pixel_size, i * pixel_size,
                        (j+1) * pixel_size, (i+1) * pixel_size)
            if translated.intersects(pixel):
                raster[height - i - 1, j] = max(raster[height - i - 1, j], floors)

# === Step 4: Display ===
plt.figure(figsize=(10, 10))
plt.imshow(raster, cmap='viridis', origin='upper')
plt.colorbar(label='Number of Floors')
plt.title("Building Footprint Raster")
plt.xlabel("X pixels")
plt.ylabel("Y pixels")

# === Step 5: Save raster ===
output_file = csv_file.replace('.csv', '.txt')
np.savetxt(output_file, raster, fmt='%d', delimiter=' ')
print(f"Raster saved to {output_file} (shape: {raster.shape})")

# === Step 6: Save raster as image ===
plt.imsave(output_file.replace('.txt', '.png'), raster, cmap='viridis')
print(f"Raster image saved to {output_file.replace('.txt', '.png')}")
