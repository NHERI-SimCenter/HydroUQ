# Require Python 3.8 or later

# Description: This script is used to post-process the EDP files selected from the StandardHydroEDP.cpp
# The EDP files may be EVT dependent, e.g. MPM vs OpenFOAM EDP time-series files are different as they are produced by different sensors/probes in the simulations
# However, this post-processor should boil them down to aggregate parameters in the same format for the fragility analysis
import numpy as np
import pandas as pd
import os
import json
import sys
import matplotlib.pyplot as plt
import matplotlib


# From StandardHydroEDP.cpp, for reference:
# QString edp1  = "max_force"; // max force on the structure or component
# QString edp2  = "max_pressure"; // max pressure  on the structure or component
# QString edp3  = "total_impulse"; // total impulse on the structure or component, integral of force-time series
# // QString edp4  = "max_wave_velocity"; // max wave velocity at a characteristic location near the structure
# // QString edp5  = "max_wave_height"; // max wave elevation at a characteristic location near the structure
# // QString edp6  = "average_wave_velocity"; // average wave elevation at a characteristic location near the structure
# // QString edp7  = "average_wave_height"; // average wave elevation at a characteristic location near the structure
# // QString edp8  = "total_wave_duration"; // wave duration based on exceeding a threshold of some variable at a characteristic location near the structure
# // QString edp9  = "total_wave_momentum_flux"; // wave momentum flux based at a characteristic location near the structure
# QString edp10 = "max_interstory_drift"; // interstory drift, i.e. max relative displacement of floor n+1 vs floor n...
# QString edp11 = "max_roof_drift"; // roof drift, i.e. max relative displacement of top floor to ground

# For MPM only:
# For Tsunami Event only:
# Using gridTarget / gridSensor files, get max_force (gridTarget[0]_dev[2].csv), total_impulse (gridTarget[0]_dev[2].csv), max_pressure (gridTarget[1]_dev[2].csv)
# TODO: Using particleTracker files, get max_interstory_drift, max_roof_drift
# Using particleTarget / particleSensor files, average_wave_height (particleTarget[0]_model[0]_dev[0].csv), get average_wave_velocity (particleTarget[4]_model[0]_dev[0].csv), total_wave_duration (particleTarget[0]_model[0]_dev[0].csv), total_wave_momentum_flux (particleTarget[0]_model[0]_dev[0].csv, particleTarget[4]_model[0]_dev[0].csv) 

# Read in files to pandas, assume they are located in the same directory as the script for now
# Read in the gridTarget files
data = {}
for i in range(2):
    for j in range(3):
        filename = f"gridTarget[{i}]_dev[{j}].csv"
        if os.path.exists(filename):
            data[filename] = pd.read_csv(filename)
        else:
            print(f"File {filename} does not exist.")

# Read in the particleTarget files            
for i in range(2):
    for j in range(3):
        for k in range(3):
            filename = f"particleTarget[{i}]_model[{k}]_dev[{j}].csv"
            if os.path.exists(filename):
                data[filename] = pd.read_csv(filename)
            else:
                print(f"File {filename} does not exist.")

EDPs = {}
# Calculate the max_force, max_pressure, total_impulse
for key in data.keys():
    if "gridTarget" in key:
        EDPs[key] = {}
        EDPs[key]["max_force"] = data[key]["force"].max()
        EDPs[key]["max_pressure"] = data[key]["pressure"].max()
        EDPs[key]["total_impulse"] = data[key]["force"].sum()
    elif "particleTarget" in key:
        EDPs[key] = {}
        EDPs[key]["average_wave_height"] = data[key]["wave_height"].mean()
        EDPs[key]["average_wave_velocity"] = data[key]["wave_velocity"].mean()
        EDPs[key]["total_wave_duration"] = data[key]["wave_duration"].sum()
        EDPs[key]["total_wave_momentum_flux"] = data[key]["wave_momentum_flux"].sum()
        
# Calculate the max_interstory_drift, max_roof_drift
for i in range(2):
    for j in range(3):
        filename = f"particleTracker[{i}]_dev[{j}].csv"
        if os.path.exists(filename):
            data = pd.read_csv(filename)
            EDPs[filename] = {}
            EDPs[filename]["max_interstory_drift"] = data["interstory_drift"].max()
            EDPs[filename]["max_roof_drift"] = data["roof_drift"].max()
        else:
            print(f"File {filename} does not exist.")
            
# Write the EDPs to a JSON file
with open("EDPs.json", "w") as f:
    json.dump(EDPs, f)
print("EDPs written to EDPs.json")
    
# Plot the EDPs
for key in EDPs.keys():
    plt.figure()
    plt.plot(EDPs[key].keys(), EDPs[key].values())
    plt.title(key)
    plt.show()
    
# Print the EDPs
for key in EDPs.keys():
    print(key)
    print(EDPs[key])
    print("\n")
    
# Print the EDPs to a CSV file
df = pd.DataFrame(EDPs)
df.to_csv("EDPs.csv")
print("EDPs written to EDPs.csv")

# Print the EDPs to a LaTeX table
df.to_latex("EDPs.tex")
print("EDPs written to EDPs.tex")

# Print the EDPs to a HTML table
df.to_html("EDPs.html")
print("EDPs written to EDPs.html")



