# -*- coding: utf-8 -*-
def draw_bathy(bathy, begin, end, output_file):
    return
# Example usage:
if __name__ == "__main__":
    # Intake bathy.txt filepath from command line. Assume data is space delimited and of form:
    # Z11 Z12 Z13 Z1N
    # Z21 Z22 Z23 Z2N
    # Z31 Z32 Z33 Z3N
    # ZM1 ZM2 ZM3 ZMN
    # Intake coordinate [x1,y1] in a list from command line
    # Intake coordinate [x2,y2] in a list from command line
    # Intake output filename from command line
    import sys
    import ast
    if len(sys.argv) != 5:
        print("Usage: python celeris_draw_bathy.py '<input_file>' '<begin coordinate>' '<end coordinate>' '<output_file>'")
        sys.exit(1)
    try:
        input_file = str(sys.argv[1])
    except ValueError:
        print("Invalid, not a filename string. Please provide an OBJ filename")
        sys.exit(1)
    try:
        begin = ast.literal_eval(sys.argv[2])
    except (SyntaxError, ValueError):
        print("Invalid begin coordinate. Please provide a list of tuples. E.g., '[(x1, y1), (x2, y2), ...]'")
        sys.exit(1)
    try:
        end = ast.literal_eval(sys.argv[3])
    except (SyntaxError, ValueError):
        print("Invalid end coordinate. Please provide a list of tuples. E.g., '[(x1, y1), (x2, y2), ...]'")
        sys.exit(1)
    try:
        output_file = str(sys.argv[4])
    except ValueError:
        print("Invalid, not a filename string. Please provide an OBJ filename")
        sys.exit(1)
    # Read the bathymetry data from the file
    with open(input_file, 'r') as f:
        lines = f.readlines()
    bathy = []
    for line in lines:
        # Split the line into a list of floats
        row = list(map(float, line.split()))
        bathy.append(row)
    # Convert the list of lists to a numpy array
    import numpy as np
    bathy = np.array(bathy)
    # Check the shape of the bathymetry data
    if len(bathy.shape) != 2:
        print("Invalid bathymetry data. Please provide a 2D array.")
        sys.exit(1)
    
    # quickly plot imshow
    import matplotlib.pyplot as plt
    im = plt.imshow(bathy, cmap='inferno', interpolation='nearest')
    plt.plot([begin[0],end[0]], [begin[1],end[1]], color='#39FF14', label='Force Sensor')
    plt.colorbar(im, label='Elevation', shrink=0.5)
    # plt.show()
    
    # Save the bathymetry image to output file
    plt.tight_layout()
    plt.savefig(output_file, dpi=100, bbox_inches='tight')
    plt.close()