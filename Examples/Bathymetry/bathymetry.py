import os
import sys
import subprocess
import numpy as np

def pip_install(package):
    try:
        __import__(package)
    except ImportError:
        try:
            print(f"Installing {package}...")
            subprocess.check_call([sys.executable, '-m', 'pip', 'install', package])
        except subprocess.CalledProcessError:
            print(f"Failed to install {package}.")
            sys.exit(1)


try:
    import mapbox_earcut as earcut
except ImportError:
    print("mapbox_earcut is not installed. Attempting to install...")
    pip_install('mapbox-earcut')
    import mapbox_earcut as earcut

def close_hole(points3d):
    """
    Triangulate a 3D horizontal polygon (constant z) with ordered points.
    Returns: list of triangle face tuples (i, j, k) into points3d.
    """
    # Step 1: Extract 2D coordinates
    coords2d = [(x, y) for x, y, _ in points3d]

    # Step 2: Flatten to 1D float32 array [x0, y0, x1, y1, ...]
    flat_coords = np.array([coord for xy in coords2d for coord in xy], dtype=np.float32).reshape(-1, 2)

    # Step 3: Create rings array (start index of each ring; only outer ring here)
    rings = np.array([flat_coords.shape[0]], dtype=np.uint32)

    # Step 4: Triangulate using correct signature
    indices = earcut.triangulate_float32(flat_coords, rings)

    # Step 5: Group into triangle face index triplets
    return [(int(indices[i]), int(indices[i+1]), int(indices[i+2]))
            for i in range(0, len(indices), 3)]

def write_extruded_obj(filename, polygon_xy, height):
    """
    Create a 3D OBJ file by extruding a 2D polygon along the Z-axis.
    
    :param filename: Name of the output OBJ file.
    :param polygon_xy: List of (x, y) tuples defining the polygon's perimeter.
    :param height: Extrusion height along the Z-axis.
    """
    polygon_xyz_back = []
    polygon_xyz_front = []
    with open(filename, 'w') as f:
        # Write bottom vertices (z=0)
        small = 1e-2
        for x, y in polygon_xy:
            f.write(f"v {x} {y} {0.0-small}\n")
            polygon_xyz_back.append((x, y, 0.0-small))
        # Write top vertices (z=height)
        for x, y in polygon_xy:
            f.write(f"v {x} {y} {height+small}\n")
            polygon_xyz_front.append((x, y, height+small))
        n = len(polygon_xy)

        # Write bottom face (reversed order for correct normal)
        #f.write("f " + " ".join(str(i + 1) for i in (range(n))) + "\n")
        
        # Write top face
        #f.write("f " + " ".join(str(i + 1 + n) for i in reversed(range(n))) + "\n")

        # Write side faces
        for i in range(n):
            next_i = (i + 1) % n
            bottom1 = i + 1
            bottom2 = next_i + 1
            top1 = bottom1 + n
            top2 = bottom2 + n
            f.write(f"f {top1} {top2} {bottom2} {bottom1}\n")

        back_face = close_hole(polygon_xyz_back)
        back_face = [(face[2], face[1], face[0]) for face in back_face]  # Reverse order for correct normal
        front_face = close_hole(polygon_xyz_front)
        for face in back_face:
            f.write(f"f {face[0] + 1} {face[1] + 1} {face[2] + 1}\n")
        for face in front_face:
            f.write(f"f {face[0] + 1 + n} {face[1] + 1 + n} {face[2] + 1 + n}\n")
        print("front face:", front_face)
        print("back face:", back_face)
    

# Example usage:
if __name__ == "__main__":
    # Intake polygon coordinates (x, y) in a list from command line
    # Assume it will be in a format like "[(x1, y1), (x2, y2), ...]"
    # For example, you can use:
    # python polygon.py "[(0, -1), (0, 0), (16.275, 0.226), (19.933, 0.226), (30.906, 1.140), (45.536, 1.750), (82.106, 1.750), (89.46, 2.363), (89.46, -1)]" 3.65
    
    import sys
    import ast
    if len(sys.argv) != 4:
        print("Usage: python bathymetry.py '<polygon_coordinates>' <height> '<output_file>'")
        sys.exit(1)
    try:
        polygon = ast.literal_eval(sys.argv[1])
    except (SyntaxError, ValueError):
        print("Invalid polygon coordinates. Please provide a list of tuples. E.g., '[(x1, y1), (x2, y2), ...]'")
        sys.exit(1)
    try:
        extrude = float(sys.argv[2])
    except ValueError:
        print("Invalid extrusion length. Please provide a numeric value. E.g., 3.65")
        sys.exit(1)
    try:
        output_file = str(sys.argv[3])
    except ValueError:
        print("Invalid, not a filename string. Please provide an OBJ filename")
        sys.exit(1)

    # polygon = [(0, 0), (16.275, 0.226), (19.933, 0.226), (30.906, 1.140), (45.536, 1.750), (82.106, 1.750), (89.46, 2.363)]  # A square    
    y_min = min(polygon, key = lambda t: t[1])[1]
    y_max = max(polygon, key = lambda t: t[1])[1]
    y_range = y_max - y_min
    if (y_range <= 0) or (y_range >= 1):
        y_range = 1
    # Assume we don't input a closed polygon, so we add two corner points below the bathymetry to finish it
    polygon.insert(0, (polygon[0][0], -y_range/4))
    polygon.append((polygon[-1][0], -y_range/4))
    # temp_file = "temp_bathymetry.obj"
    write_extruded_obj(output_file, polygon, extrude)
    # close_mesh(temp_file, output_file)

