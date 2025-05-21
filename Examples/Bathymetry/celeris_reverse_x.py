import argparse

def reverse_columns(input_file, output_file):
    try:
        with open(input_file, 'r') as infile:
            lines = infile.readlines()

        with open(output_file, 'w') as outfile:
            for line_num, line in enumerate(lines, start=1):
                stripped_line = line.strip()
                if not stripped_line:
                    continue  # skip empty lines

                elements = stripped_line.split()
                reversed_elements = elements[::-1]
                outfile.write(' '.join(reversed_elements) + '\n')

        print(f"Reversed columns saved to {output_file}")

    except FileNotFoundError:
        print(f"Error: File '{input_file}' not found.")
    except Exception as e:
        print(f"An error occurred on line {line_num}: {e}")

def main():
    parser = argparse.ArgumentParser(description="Reverse the order of columns in a 2D space-delimited text file.")
    parser.add_argument("input_file", help="Path to the input text file")
    parser.add_argument("output_file", help="Path to the output text file")
    args = parser.parse_args()

    reverse_columns(args.input_file, args.output_file)

if __name__ == "__main__":
    main()
