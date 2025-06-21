import os
import argparse

def create_config(out_path, 
                  width=None, 
                  height=None, 
                  dx=1.00000000, 
                  dy=1.00000000,
                  Courant_num=0.100000,
                  NLSW_or_Bous=1.00000000,
                  base_depth=2.50000000, # average of depth under sea level at boundaries
                  g=9.80665000, # shouldn't be changed
                  Theta=2.00000000,
                  friction=0.00100000,
                  isManning=0.00000000,
                  dissipation_threshold=0.15000000,
                  whiteWaterDecayRate=0.02000000,
                  timeScheme=2.00000000,
                  seaLevel=0.00000000,
                  Bcoef=0.06666667,
                  tridiag_solve=2.00000000,
                  west_boundary_type=0.00000000,  # 0=solid wall, 1=sponge layer, 2=waves loaded from file
                  east_boundary_type=0.00000000,  # 0=solid wall, 1=sponge layer, 2=waves loaded from file
                  south_boundary_type=0.00000000, # 0=solid wall, 1=sponge layer, 2=waves loaded from file
                  north_boundary_type=0.00000000, # 0=solid wall, 1=sponge layer, 2=waves loaded from file
                  WaveType=-1.0, # -1=file, 0,1,2=sine wave, 3=solitary wave
                  lat_LL=-122.341,  # lower left corner latitude
                  lon_LL=37.8992,  # lower left corner longitude
                  lat_UR=-122.323,  # upper right corner latitude
                  lon_UR=37.9151   # upper right corner longitude
                  ): #TODO: add parameters
  if not width:
    raise Exception("width not given")
  if not height:
    raise Exception("height not given")
  text = "{"
  text += "\n  " + f'''"WIDTH": {width}.00000000,''' # not sure if # of sig figs is important
  text += "\n  " + f'''"HEIGHT": {height}.00000000,''' # not sure if # of sig figs is important
  text += "\n  " + f'''"dx": {round(dx,8)},'''
  text += "\n  " + f'''"dy": {round(dy,8)},'''
  text += "\n  " + f'''"Courant_num": {Courant_num},'''
  text += "\n  " + f'''"NLSW_or_Bous": {NLSW_or_Bous},'''
  text += "\n  " + f'''"base_depth": {base_depth},'''
  text += "\n  " + f'''"g": {g},'''
  text += "\n  " + f'''"Theta": {Theta},'''
  text += "\n  " + f'''"friction": {friction},'''
  text += "\n  " + f'''"isManning": {isManning},'''
  text += "\n  " + f'''"dissipation_threshold": {dissipation_threshold},'''
  text += "\n  " + f'''"whiteWaterDecayRate": {whiteWaterDecayRate},'''
  text += "\n  " + f'''"timeScheme": {timeScheme},'''
  text += "\n  " + f'''"seaLevel": {seaLevel},'''
  text += "\n  " + f'''"Bcoef": {Bcoef},'''
  text += "\n  " + f'''"tridiag_solve": {tridiag_solve},'''
  text += "\n  " + f'''"west_boundary_type": {west_boundary_type},'''
  text += "\n  " + f'''"east_boundary_type": {east_boundary_type},'''
  text += "\n  " + f'''"south_boundary_type": {south_boundary_type},'''
  text += "\n  " + f'''"north_boundary_type": {north_boundary_type},'''
  text += "\n  " + f'''"WaveType": {WaveType},'''
  text += "\n  " + f'''"lat_LL": {lat_LL},'''
  text += "\n  " + f'''"lon_LL": {lon_LL},'''
  text += "\n  " + f'''"lat_UR": {lat_UR},'''
  text += "\n  " + f'''"lon_UR": {lon_UR}'''
  text += "\n}"
  with open(out_path, "w") as f:
    f.write(text)

if __name__ == "__main__": # For testing purposes
  __location__ = os.path.realpath(os.path.join(os.getcwd(), os.path.dirname(__file__)))
  parser = argparse.ArgumentParser(description="Create a configuration file for CelerisInit.")
  parser.add_argument("--output_directory", type=str, default="CelerisInit", help="Output directory for the config file.")
  parser.add_argument("--output_filename", type=str, default="config.json", help="Output filename for the config file.")
  filename = os.path.join(__location__, parser.parse_args().output_directory, parser.parse_args().output_filename)
  create_config(filename, 
                width=1147, 
                height=718,
                dx=1.0000000,
                dy=1.0000000,
                south_boundary_type=2.00000000)
  