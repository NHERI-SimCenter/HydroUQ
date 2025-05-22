import argparse

def convert_feet_to_meters(input_file, output_file):
    try:
        with open(input_file, 'r') as infile:
            lines = infile.readlines()

        with open(output_file, 'w') as outfile:
            for line in lines:
                feet_values = line.strip().split()
                meter_values = [str(round(float(val) * 0.3048, 4)) for val in feet_values]
                outfile.write(' '.join(meter_values) + '\n')

        print(f"Converted elevations saved to {output_file}")

    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found.")
    except ValueError:
        print("Error: Ensure the input file contains only numeric values.")
    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    parser = argparse.ArgumentParser(description="Convert elevation data from feet to meters.")
    parser.add_argument("input_file", help="Path to the input text file with elevations in feet")
    parser.add_argument("output_file", help="Path to the output text file with elevations in meters")
    args = parser.parse_args()

    convert_feet_to_meters(args.input_file, args.output_file)

if __name__ == "__main__":
    main()
