import math
import os

def create_waves(out_path, numwaves, amplitude, period, direction, phase): # TODO: add parameters
  text = f"""\n[NumberOfWaves] {numwaves}\n================================="""
  for i in range(numwaves):
    text = text + "\n" + str(amplitude[i]) + "      " + str(period[i]) + "     " + str(direction[i]) + "      " + str(phase[i])
  with open(out_path, "w") as f:
    f.write(text)


if __name__ == "__main__": # For testing purposes
  numwaves = 1
  amplitude, period, direction, phase = ([5 for _ in range(numwaves)],
                                         [5 for _ in range(numwaves)],
                                         [math.pi/2 for _ in range(numwaves)],
                                         [0 for _ in range(numwaves)])
  __location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
  filename = os.path.join(__location__, "CelerisInit/waves.txt")
  create_waves(filename, numwaves, amplitude, period, direction, phase)

# The value after the [NumberOfWaves] represents the total number of individual wave components you wish to generate.  So, to generate a monochromatic wave, this would be 1.   The data columns are:
# Column 1: Wave component amplitude (m)
# Column 2: Wave period (sec)
# Column 3: Wave direction (rad)
# Column 4: Wave phase (rad)