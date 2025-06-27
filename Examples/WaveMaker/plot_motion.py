import argparse
import csv
import matplotlib.pyplot as plt
import numpy as np
import os

def parse_csv(file_path):
    print(f"Parsing CSV file: {file_path}")
    """Parse the CSV file and return time, displacement, and velocity as numpy arrays."""
    if not file_path.endswith('.csv'):
        raise ValueError("Input file must be a CSV file.")
    if not file_path:
        raise ValueError("Input file path is required.")
    print("Reading CSV data...")
    # Initialize lists to store data
    if not os.path.exists(file_path):
        raise FileNotFoundError(f"File not found: {file_path}")
    
    time, displacement, velocity = [], [], []
    with open(file_path, 'r') as f:
        reader = csv.reader(f)
        for row in reader:
            if all(cell.strip().replace('.', '', 1).replace('-', '', 1).isdigit() for cell in row):
                time.append(float(row[0]))
                displacement.append(float(row[1]))
                velocity.append(float(row[2]))
    return np.array(time), np.array(displacement), np.array(velocity)

def plot_data(time, displacement, velocity):
    print("Plotting data...")
    
    # --- Matplotlib PNG Output ---
    fig, ax1 = plt.subplots(figsize=(10, 6))

    color1 = 'blue'
    ax1.set_xlabel('Time (s)')
    ax1.set_ylabel('Displacement (m)', color=color1)
    ax1.plot(time, displacement, color=color1, label='Displacement')
    ax1.tick_params(axis='y', labelcolor=color1)

    ax2 = ax1.twinx()
    color2 = 'red'
    ax2.set_ylabel('Velocity (m/s)', color=color2)
    ax2.plot(time, velocity, color=color2, linestyle='--', label='Velocity')
    ax2.tick_params(axis='y', labelcolor=color2)

    # fig.tight_layout()
    # plt.title('Custom Wavemaker Time Series')
    print("Saving plot as PNG...")
    # save the plot as a png file located adjacent to the script
    fn = os.path.join(os.path.dirname(__file__), 'custom_wavemaker.png')
    
    plt.savefig(fn, format='png', bbox_inches='tight')
    print(f"Plot saved as {fn}")
    # plt.savefig('custom_wavemaker.html', format='svg')  # Save as SVG for HTML compatibility
    plt.close()

def main():
    parser = argparse.ArgumentParser(description='Plot displacement and velocity vs. time.')
    parser.add_argument('--input', '-i', type=str, required=True, help='Path to input CSV file')
    args = parser.parse_args()
    
    print(f"Reading data from {args.input}")
    if not args.input.endswith('.csv'):
        raise ValueError("Input file must be a CSV file.")
    print("Parsing CSV data...")
    if not args.input:
        raise ValueError("Input file path is required.")

    time, displacement, velocity = parse_csv(args.input)
    plot_data(time, displacement, velocity)

if __name__ == '__main__':
    main()
