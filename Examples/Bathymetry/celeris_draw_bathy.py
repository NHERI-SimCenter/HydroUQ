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
    if len(sys.argv) < 8:
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
        print("Invalid begin coordinate. Please provide a list. E.g., '[x1, y1]'")
        sys.exit(1)
    try:
        end = ast.literal_eval(sys.argv[3])
    except (SyntaxError, ValueError):
        print("Invalid end coordinate. Please provide a list. E.g., '[x2, y2]'")
        sys.exit(1)
    try:
        wave_gauges = ast.literal_eval(sys.argv[4])
    except (SyntaxError, ValueError):
        print("Invalid wave gauges. Please provide a list of tuples. E.g., '[(x1, y1), (x2, y2), ...]'")
        sys.exit(1)
    try:
        dx = float(sys.argv[5])
    except ValueError:
        print("Invalid, not a number. Please provide a number for grid-spacing dx, E.g., 0.1")
    try:
        dy = float(sys.argv[6])
    except ValueError:
        print("Invalid, not a number. Please provide a number for grid-spacing dy, E.g., 0.1")
    try:
        output_file = str(sys.argv[7])
    except ValueError:
        print("Invalid, not a filename string. Please provide an OBJ filename")
        sys.exit(1)
    try:
        bbox = ast.literal_eval(sys.argv[8])
    except:
        bbox = None
        # print("No bounding box provided, defaulting to meters as length unit. Bbox providable as a list of 4 floats, e.g., '[lon_LL, lat_LL, lon_UR, lat_UR]'")
        
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
    im = plt.imshow(bathy, cmap='terrain', interpolation='None', origin='lower')
    plt.plot([begin[0],end[0]], [begin[1],end[1]], color='black', label='Force Sensor')
    plt.text(begin[0], begin[1], "FS", fontsize=7, ha='right', va='bottom', color='#39FF14')
    
    # plot wave gauges
    i = 0
    for gauge in wave_gauges:
        plt.plot(gauge[0]/dx, gauge[1]/dy, 'o', color='black', label='Wave Gauge', markersize=2)
        plt.text(gauge[0]/dx, gauge[1]/dy, "WG"+str(i), fontsize=7, ha='right', va='bottom', color='cyan')
        i += 1
        
    if bbox is not None:
        plt.gca().set_ylim(0, bathy.shape[0])
        plt.gca().set_xlim(0, bathy.shape[1])
        plt.gca().set_yticks([0, 0.25 * bathy.shape[0], 0.5 * bathy.shape[0], 0.75 * bathy.shape[0], bathy.shape[0]])
        plt.gca().set_xticks([0, 0.25 * bathy.shape[1], 0.5 * bathy.shape[1], 0.75 * bathy.shape[1], bathy.shape[1]])
        plt.gca().set_xticklabels([f"{x:.4f}" for x in [bbox[0], (bbox[0] + (bbox[2] - bbox[0]) / 4), (bbox[0] + (bbox[2] - bbox[0]) / 2), (bbox[0] + 3 * (bbox[2] - bbox[0]) / 4), (bbox[2])]], rotation=30)
        plt.gca().set_yticklabels([f"{y:.4f}" for y in [bbox[1], (bbox[1] + (bbox[3] - bbox[1]) / 4), (bbox[1] + (bbox[3] - bbox[1]) / 2), (bbox[1] + 3 * (bbox[3] - bbox[1]) / 4), (bbox[3])]], rotation=30)
        plt.gca().tick_params(axis='both', direction='out', length=4, width=1, colors='black', labelsize=8)
        plt.gca().set_xlabel('Longitude (degrees)', fontsize=8)
        plt.gca().set_ylabel('Latitude (degrees)', fontsize=8)
    else:
        xticks = [0, 0.125 * bathy.shape[1], 0.25 * bathy.shape[1], 0.375 * bathy.shape[1], 0.5 * bathy.shape[1], 0.625 * bathy.shape[1], 0.75 * bathy.shape[1], 0.875 * bathy.shape[1], bathy.shape[1]]
        yticks = [0, 0.125 * bathy.shape[0], 0.25 * bathy.shape[0], 0.375 * bathy.shape[0], 0.5 * bathy.shape[0], 0.625 * bathy.shape[0], 0.75 * bathy.shape[0], 0.875 * bathy.shape[0], bathy.shape[0]]
        plt.gca().set_xticks(xticks)
        plt.gca().set_yticks(yticks)
        plt.gca().set_xticklabels([f"{x*dx:.2f}" for x in xticks], rotation=30)
        plt.gca().set_yticklabels([f"{y*dy:.2f}" for y in yticks], rotation=30)
        plt.gca().tick_params(axis='both', direction='out', length=4, width=1, colors='black', labelsize=8)
        plt.gca().set_xlabel('X (m)', fontsize=8)
        plt.gca().set_ylabel('Y (m)', fontsize=8)
    plt.colorbar(im, label='Elevation', shrink=0.5)
    # plt.show()
    
    # Save the bathymetry image to output file
    plt.tight_layout()
    plt.savefig(output_file, dpi=150, bbox_inches='tight')
    plt.close()
