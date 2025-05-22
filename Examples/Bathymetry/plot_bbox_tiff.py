import argparse
import rasterio
from rasterio.windows import Window
import matplotlib.pyplot as plt
from matplotlib.colors import LogNorm, SymLogNorm
import numpy as np
import os
import sys

def load_and_plot_bbox(tif_path, col_off, row_off, width, height):
    """
    Loads and plots a bounding box from a large TIFF file.

    Parameters:
    - tif_path: Path to the .tif file
    - col_off: Column offset (x offset in pixels)
    - row_off: Row offset (y offset in pixels)
    - width: Width of the window in pixels
    - height: Height of the window in pixels
    """
    with rasterio.open(tif_path) as src:
        print(f"Image size: {src.width} columns x {src.height} rows")

        # Clip window dimensions to avoid going out of bounds
        col_off = max(0, col_off)
        row_off = max(0, row_off)
        width = min(width, src.width - col_off)
        height = min(height, src.height - row_off)

        window = Window(col_off, row_off, width, height)
        data = src.read(1, window=window)
        # Replace invalid or extreme values
        print("Data max:", data.max())
        print("Data min:", data.min())
        print("Contains nans:", np.isnan(data).any())
        print("Contains infs:", np.isinf(data).any())
        
        print("Remove nans")
        data = np.where(np.isnan(data), 0, data)
        data = np.where(data > 1e9, 0, data)  # Mask huge values
        data = np.where(data < -1e20, 0, data)  # Mask huge values
        print("Data max:", data.max())
        print("Data min:", data.min())
        # data -= data.min()  # Shift to positive values
        # print("Data min after shift:", data.min())
        # print("Data max after shift:", data.max())
        # data = np.where(data <= 0, 1e-3, data)  # Avoid log(0); clip to small positive


        # Normalize the data to 0–1 for visualization
        print("Data max:", data.max())
        print("Data min:", data.min())
        print("Data shape:", data.shape)
        print("Data dtype:", data.dtype)
        print("Data size:", data.size)
        # data_min = np.percentile(data, 0)
        # data_max = np.percentile(data, 100)
        # data_clipped = np.clip(data, data_min, data_max)
        # data_norm = (data_clipped - data_min) / (data_max - data_min + 1e-6)
        # print("Data norm min:", data_norm.min())
        # print("Data norm max:", data_norm.max())
        # print("Data norm shape:", data_norm.shape)
        # print("Data norm dtype:", data_norm.dtype)
        
        # Save data to a space-delimited .txt file
        base_name = os.path.splitext(os.path.basename(tif_path))[0]
        txt_filename = f"{base_name}_x{col_off}_y{row_off}_w{width}_h{height}.txt"
        np.savetxt(txt_filename, data, fmt="%.3f", delimiter=" ")
        print(f"Saved data to: {txt_filename}")
        
        
        # data = (data_norm * 255).astype('uint8')
        # Percentile-based limits for LogNorm
        vmin = np.percentile(data, 0)
        vmax = np.percentile(data, 100)
        linthresh = max((vmax - vmin) * 0.01, 1e-3)  # threshold for linear behavior near 0
        plt.imshow(data, cmap='gray',norm=SymLogNorm(linthresh=linthresh, linscale=1, vmin=vmin, vmax=vmax)) #norm=LogNorm(vmin=vmin, vmax=vmax))
        plt.title(f"BBox: x={col_off}, y={row_off}, w={width}, h={height}")
        plt.axis('off')
        plt.colorbar(label='Log-scaled pixel values')
        plt.savefig(f"{base_name}_x{col_off}_y{row_off}_w{width}_h{height}.png", dpi=300)
        print(f"Saved plot to: {base_name}_x{col_off}_y{row_off}_w{width}_h{height}.png")
        plt.show()
        # plt.close()
        

def main():
    parser = argparse.ArgumentParser(description="Load and plot a bounding box from a large TIFF file.")
    parser.add_argument("tif_path", help="Path to the TIFF file")
    parser.add_argument("col_off", type=int, help="Column offset (x)")
    parser.add_argument("row_off", type=int, help="Row offset (y)")
    parser.add_argument("width", type=int, help="Width of the bounding box")
    parser.add_argument("height", type=int, help="Height of the bounding box")

    args = parser.parse_args()

    load_and_plot_bbox(
        tif_path=args.tif_path,
        col_off=args.col_off,
        row_off=args.row_off,
        width=args.width,
        height=args.height
    )

if __name__ == "__main__":
    main()
