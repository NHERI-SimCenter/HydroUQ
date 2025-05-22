import argparse

def reverse_rows(input_file, output_file):
    try:
        # Read the data from the input file
        with open(input_file, 'r') as f:
            lines = f.readlines()

        # Reverse the order of rows
        reversed_lines = lines[::-1]

        # Write the reversed data to the output file
        with open(output_file, 'w') as f:
            for line in reversed_lines:
                # Clean and reformat line
                numbers = line.strip().split()
                f.write(' '.join(numbers) + '\n')

        print(f"Reversed data saved to {output_file}")

    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

def main():
    parser = argparse.ArgumentParser(description="Reverse the order of rows in a 2D space-delimited text file.")
    parser.add_argument("input_file", help="Path to the input text file")
    parser.add_argument("output_file", help="Path to the output text file")

    args = parser.parse_args()
    reverse_rows(args.input_file, args.output_file)

if __name__ == "__main__":
    main()
