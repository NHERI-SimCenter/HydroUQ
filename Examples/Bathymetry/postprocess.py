import numpy as np
import matplotlib.pyplot as plt
import os
import argparse

def main():
    """
    Displays three vertically stacked plots for wave gauge elevations,
    velocity, and force sensor time series data respectively.
    """
    parser = argparse.ArgumentParser(description="Post-process Celeris simulation data.")
    parser.add_argument("-d", "--directory", type=str, default=".", help="Directory containing the output files.")
    args = parser.parse_args()
    directory = args.directory

    required_files = ["wave_gauge.csv", "velocity.csv", "forces.csv"]
    for fname in required_files:
        if not os.path.isfile(os.path.join(directory, fname)):
            print(f"Error: {fname} not found in {directory}")
            return

    wave_gauge = np.genfromtxt(os.path.join(directory, "wave_gauge.csv"), delimiter=",", skip_header=1, filling_values=np.nan)
    velocity = np.genfromtxt(os.path.join(directory, "velocity.csv"), delimiter=",", skip_header=1, filling_values=np.nan)
    force = np.genfromtxt(os.path.join(directory, "forces.csv"), delimiter=",", skip_header=1, filling_values=np.nan)

    # Set up figure with larger size
    fig, axes = plt.subplots(3, 1, sharex=True, figsize=(12, 10))
    plt.subplots_adjust(hspace=0.35)

    # Use larger font sizes
    title_font = {'fontsize': 10, 'fontweight': 'bold'}
    label_font = {'fontsize': 10}
    tick_fontsize = 8

    # Wave gauge elevations plot
    time = wave_gauge[:, 0]
    for i in range(1, wave_gauge.shape[1]):
        axes[0].plot(time, wave_gauge[:, i], label=f"Gauge {i}", alpha=0.8)
    axes[0].set_ylabel("Elevation (m)", **label_font)
    axes[0].set_title("Wave Gauge Elevations", **title_font)
    axes[0].grid(True, linestyle=':', alpha=0.6)
    axes[0].legend(fontsize=8, ncol=4, loc='upper right')
    axes[0].tick_params(axis='both', labelsize=tick_fontsize)

    # Velocities plot
    time = velocity[:, 0]
    num_vel = (velocity.shape[1] - 1) // 2
    for i in range(num_vel):
        axes[1].plot(time, velocity[:, 1 + 2*i], label=f"Velocimeter {i+1} (X)", alpha=0.8)
        axes[1].plot(time, velocity[:, 2 + 2*i], label=f"Velocimeter {i+1} (Y)", linestyle='--', alpha=0.8)
    axes[1].set_ylabel("Velocity (m/s)", **label_font)
    axes[1].set_title("Velocimeter Readings", **title_font)
    axes[1].grid(True, linestyle=':', alpha=0.6)
    axes[1].legend(fontsize=8, ncol=4, loc='upper right')
    axes[1].tick_params(axis='both', labelsize=tick_fontsize)

    # Forces plot
    time = force[:, 0]
    labels = ["Hydrostatic", "Current U", "Current V", "Total Force"]
    styles = ['-', '--', ':', '-.']
    for i in range(1, min(5, force.shape[1])):
        axes[2].plot(time, force[:, i], label=labels[i-1], linestyle=styles[i-1], alpha=0.9)
    axes[2].set_ylabel("Force (N)", **label_font)
    axes[2].set_xlabel("Time (s)", **label_font)
    axes[2].set_title("Forces on Sensor", **title_font)
    axes[2].grid(True, linestyle=':', alpha=0.6)
    axes[2].legend(fontsize=8, loc='upper right')
    axes[2].tick_params(axis='both', labelsize=tick_fontsize)

    # Save the figure
    output_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), "results.png")
    plt.savefig(output_path, dpi=100)
    print(f"Results saved to {output_path}")

if __name__ == "__main__":
    main()