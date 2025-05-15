def write_extruded_obj(filename, polygon_xy, height):
    """
    Create a 3D OBJ file by extruding a 2D polygon along the Z-axis.
    
    :param filename: Name of the output OBJ file.
    :param polygon_xy: List of (x, y) tuples defining the polygon's perimeter.
    :param height: Extrusion height along the Z-axis.
    """
    with open(filename, 'w') as f:
        # Write bottom vertices (z=0)
        for x, y in polygon_xy:
            f.write(f"v {x} {y} 0.0\n")
        # Write top vertices (z=height)
        for x, y in polygon_xy:
            f.write(f"v {x} {y} {height}\n")

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
    write_extruded_obj(output_file, polygon, extrude)

