% Script to create input files needed for Unity version of Celeris
% creates config.json, irrWaves.txt, and modified_bathy.txt

clear all
close all
clf

% High-Level Simulation Control Parameters
NLSW_or_Bous =1; % =0 for Nonlinear Shallow Water Solver (long waves only) otherwise Boussinesq (wind waves) 
dx=2.25; % uniform grid size to use in model - the loaded bathy files will be interpolated to this grid size
Courant_num = 0.2; %Target Courant #.  ~0.25 for P-C, ~0.05 for explicit methods. Default: 0.2
isManning=0; % A boolean friction model value, if==1 "friction" is a Mannnigs n, otherwise it is a dimensionless friction factor (Moody)
friction=0.001;  % dimensionless friction coefficient, or Mannings "n", depending on isManning choice

% Waves
Hmo=5.;  % Spectral wave height (m)
Tp=10;  % peak period (sec)
Thetap=0; % mean direction (deg w.r.t. numerical grid) 0=from west, 90=from south, 180=from east, -90 or 270 from north

%  Boundary conditions - at least one of the boundaries should be = 2
west_boundary_type=2; % west_boundary_type, 0=solid wall, 1=sponge layer, 2= waves loaded from file, created by spectrum_2D above
east_boundary_type=1; % east_boundary_type, 0=solid wall, 1=sponge layer, 2= waves loaded from file, created by spectrum_2D above
south_boundary_type=1; % south_boundary_type, 0=solid wall, 1=sponge layer, 2= waves loaded from file, created by spectrum_2D above
north_boundary_type=1; % north_boundary_type, 0=solid wall, 1=sponge layer, 2= waves loaded from file, created by spectrum_2D above

% Defaults, should not need to change (for other parameters need to change source code
g=9.81;  %gravity
Theta=1.5;  %midmod limiter parameter; empirical breaking parameter. 1.0 most dissipative (upwind) to 2.0 least dissipative (centered) Default: 1.5
dissipation_threshold=0.3;  %For visualization purposes, represents a characterestic slope at breaking. 0.577=30 degrees, will need to be lower for coarse grid simulations that can not resolve this slope; 0.364=20 deg; 0.2679=15 deg
whiteWaterDecayRate=0.9; % For visualization purposes, not simulation. Default: 0.9
timeScheme=2;  %  Time integration choices: 0=Euler, 1=3rd-order A-B predictor, 2= A-B 4th-order predictor+corrector. Default: 2
seaLevel=0.0;  % water level shift from given datum, for tide, surge, etc
Bcoef=0.06666667; % dispersion parameter, 1/15 is optimum value for this set of equations. Default: 0.06666666666667
tridiag_solve=2; % Method to solve the tridiagonal Boussinesq system: =0 Thomas (extremely slow, only for small domains (nx,ny <500) due to thread memory req), =1 Gauss-Sid (very slow), or 2 parallel cyclic reduction (best). Default: 2 

% Create bathy/topo surface - this needs to be custom for each scenario -
% see the interpBathy.m script in the directory below to see how the data
% is converted into a model grid
load celeris_bathy.mat

% for cases that we know the mapped lat and lon
lon_LL=min(lon);
lat_LL=min(lat);
lon_UR=max(lon);
lat_UR=max(lat);
GoogleMapOverlay = 1;

% fit data to simulation dx // flip miami to fit on screen
x_interp=x(1):dx:x(end);
y_interp=y(1):dx:y(end);
h_interp=interp2(x,y',h,x_interp,y_interp')+seaLevel;
[ny,nx]=size(h_interp);


base_depth=-min(min(h_interp)); % characteristic_depth (m), used to estimate time step, use depth in area of wave generation, or expected largest depth in domain
%h_interp = h_interp*0 - base_depth;
figure(1)
clf
pcolor(x_interp,y_interp,h_interp)
axis equal
shading interp
colorbar



pause(.1)
save bathy.txt h_interp -ascii

WIDTH=length(x_interp); % //WIDTH
HEIGHT=length(y_interp); % //HEIGHT
dx=mean(diff(x_interp));  % //dx
dy=mean(diff(y_interp));  %  //dy

% create spectral waves
spectrum_2D(Hmo,Tp,Thetap,base_depth);   % creates input wave spectrum

% write sim control data to file
data = [ WIDTH, HEIGHT, dx, dy, Courant_num, NLSW_or_Bous, ...
            base_depth, g, Theta, friction, isManning, ...
            dissipation_threshold, whiteWaterDecayRate, timeScheme, ...
            seaLevel*0, Bcoef, tridiag_solve, west_boundary_type, ...
            east_boundary_type, south_boundary_type, north_boundary_type, Hmo, ...
            lat_LL, lon_LL, lat_UR, lon_UR, GoogleMapOverlay];
varnames = {'WIDTH', 'HEIGHT', 'dx', 'dy', 'Courant_num', 'NLSW_or_Bous', ...
            'base_depth', 'g', 'Theta', 'friction', 'isManning', ...
            'dissipation_threshold', 'whiteWaterDecayRate', 'timeScheme', ...
            'seaLevel', 'Bcoef', 'tridiag_solve', 'west_boundary_type', ...
            'east_boundary_type', 'south_boundary_type', 'north_boundary_type', 'significant_wave_height', ...
            'lat_LL', 'lon_LL', 'lat_UR', 'lon_UR', 'GoogleMapOverlay'};

% Open the output file for writing
fid = fopen('config.json', 'w');
fprintf(fid, '{ \n');
% Write the data and variable names to the file
for i = 1:length(data)-1
    fprintf(fid, '  "%s": %.8f, \n' ,varnames{i} , data(i));
end
i=i+1;
fprintf(fid, '  "%s": %.8f \n' ,varnames{i} , data(i));
fprintf(fid, '} \n');

% Close the output file
fclose(fid);






