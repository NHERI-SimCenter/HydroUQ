import numpy as np
import argparse
import matplotlib.pyplot as plt
import os

def generate_bathymetry(xz_coords, y_length, sea_level, dx, dy):
    # Extract X and Z values from the coordinates
    xz_coords = np.array(xz_coords)
    x_vals = xz_coords[:, 0]
    z_vals = xz_coords[:, 1]

    # Determine grid size
    x_min, x_max = x_vals.min(), x_vals.max()
    nx = int((x_max - x_min) / dx) + 1
    ny = int(y_length / dy) + 1

    # Create X grid for interpolation
    x_grid = np.linspace(x_min, x_max, nx)

    # Interpolate elevation values along X
    z_profile = np.interp(x_grid, x_vals, z_vals)
    z_profile = z_profile - sea_level  # Adjust for sea level
    
    # Repeat this profile along Y
    bathymetry = np.tile(z_profile, (ny, 1))

    return bathymetry

def save_bathymetry_txt(bathymetry, filename):
    np.savetxt(filename, bathymetry, fmt='%.3f', delimiter=' ')
    print(f"Bathymetry saved to {filename} (shape: {bathymetry.shape})")

def save_bathymetry_plot(bathymetry, output_base):
    plt.figure(figsize=(10, 6))
    plt.imshow(bathymetry, cmap='terrain', origin='lower', aspect='auto')
    plt.colorbar(label='Elevation (Z)')
    plt.title('Generated Bathymetry')
    plt.xlabel('X pixels')
    plt.ylabel('Y pixels')

    image_file = f"{output_base}.png"
    plt.savefig(image_file, dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Plot saved to {image_file}")

def main():
    parser = argparse.ArgumentParser(description="Generate simple bathymetry by extruding XZ profile.")
    parser.add_argument('--coords', type=str, required=True,
                        help='List of coordinates in format [[X1,Z1],[X2,Z2],...]. Use quotes.')
    parser.add_argument('--y_length', type=float, required=True,
                        help='Extrusion length in Y-direction.')
    parser.add_argument('--swl', type=float, default=0.0, required=True,
                        help='Sea Water Level (SWL) in Z-direction.')
    parser.add_argument('--dx', type=float, required=True, help='Pixel size in X.')
    parser.add_argument('--dy', type=float, required=True, help='Pixel size in Y.')
    parser.add_argument('--output', type=str, required=True, help='Output .txt filename.')

    args = parser.parse_args()

    # Convert input coordinates from string to list
    try:
        xz_coords = eval(args.coords)
        if not isinstance(xz_coords, list) or not all(len(pair) == 2 for pair in xz_coords):
            raise ValueError
    except Exception:
        raise ValueError("Invalid format for --coords. Use format like: \"[[0,-10],[50,-20],[100,0]]\"")

    # Generate bathymetry
    bathymetry = generate_bathymetry(xz_coords, args.y_length, args.swl, args.dx, args.dy)

    # Save as space-delimited text
    save_bathymetry_txt(bathymetry, args.output)

    # Save plot
    output_base = os.path.splitext(args.output)[0]
    save_bathymetry_plot(bathymetry, output_base)

if __name__ == "__main__":
    main()