import numpy as np
import matplotlib.pyplot as plt
import argparse
import ast
import os

def parse_arguments():
    parser = argparse.ArgumentParser(
        description="Merge multiple bathymetry files with translation and Z-scaling."
    )
    parser.add_argument('inputs', nargs='+',
                        help='Sequence of file translation scale triplets. Example: bathy.txt "[100,200]" 1.0')
    parser.add_argument('--output', type=str, default='merged_bathymetry.txt',
                        help='Output filename (space-delimited TXT).')
    return parser.parse_args()

def read_and_scale_bathymetry(file_path, scale):
    data = np.loadtxt(file_path)
    return data * scale

def place_in_canvas(canvas, data, start_x, start_y):
    h, w = data.shape
    canvas[start_y:start_y+h, start_x:start_x+w] += data
    return canvas

def compute_canvas_size(instructions):
    max_x, max_y = 0, 0
    for file, (x, y), _ in instructions:
        data = np.loadtxt(file)
        height, width = data.shape
        max_x = max(max_x, x + width)
        max_y = max(max_y, y + height)
    return max_y, max_x

def main():
    args = parse_arguments()
    input_args = args.inputs

    if len(input_args) % 3 != 0:
        raise ValueError("Each input must have 3 values: file, translation, and scale.")

    # Parse inputs
    instructions = []
    for i in range(0, len(input_args), 3):
        file_path = input_args[i]
        translation = ast.literal_eval(input_args[i+1])
        if not isinstance(translation, list) or len(translation) != 2:
            raise ValueError(f"Invalid translation: {translation}")
        scale = float(input_args[i+2])
        instructions.append((file_path, translation, scale))

    # Determine size of the output canvas
    canvas_height, canvas_width = compute_canvas_size(instructions)
    canvas = np.zeros((canvas_height, canvas_width), dtype=np.float32)

    # Merge files
    for file_path, (x_offset, y_offset), scale in instructions:
        data = read_and_scale_bathymetry(file_path, scale)
        h, w = data.shape

        # Check bounds
        if y_offset + h > canvas.shape[0] or x_offset + w > canvas.shape[1]:
            raise ValueError(f"File {file_path} at ({x_offset},{y_offset}) exceeds canvas size.")

        canvas[y_offset:y_offset+h, x_offset:x_offset+w] += data
        print(f"Merged {file_path} at ({x_offset},{y_offset}) with scale {scale}")

    # Save the result
    np.savetxt(args.output, canvas, fmt='%.3f', delimiter=' ')
    print(f"Saved merged bathymetry to {args.output} (shape: {canvas.shape})")

    # Optionally, save a plot
    plt.imshow(canvas, cmap='terrain', origin='lower', aspect='auto')
    plt.colorbar(label='Elevation (Z)')
    plt.title('Merged Bathymetry')
    plt.xlabel('X pixels')
    plt.ylabel('Y pixels')
    plt.savefig(args.output.replace('.txt', '.png'), dpi=300, bbox_inches='tight')
    plt.close()
    print(f"Plot saved to {args.output.replace('.txt', '.png')}")


if __name__ == "__main__":
    main()
