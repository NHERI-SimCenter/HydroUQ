clc
clear all
close all


currData='PressureProbe1/0/p'
opts = detectImportOptions(currData);
opts.DataLines=4;
opts.SelectedVariableNames = [1,2]; 
opts.Delimiter='  ';

data=readmatrix(currData,opts);
p1FYS=data;


currData='PressureProbe2/0/p'
opts = detectImportOptions(currData);
opts.DataLines=4;
opts.SelectedVariableNames = [1,2]; 
opts.Delimiter='  ';

data=readmatrix(currData,opts);
p2FYS=data;


currData='PressureProbe3/0/p'
opts = detectImportOptions(currData);
opts.DataLines=4;
opts.SelectedVariableNames = [1,2]; 
opts.Delimiter='  ';

data=readmatrix(currData,opts);
p3FYS=data;



currData='WaveGauge1/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG1FYS=data;

currData='WaveGauge2/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG2FYS=data;

currData='WaveGauge3/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG3FYS=data;

currData='VelocityProbe1/0/U'

fid  = fopen(currData,'r');
f=fread(fid,'*char')';
f = strrep(f,'(','');
f = strrep(f,')','');
f = strrep(f,'	',' ');

for i =1:100;

f = strrep(f,'  ',' ');

end
fclose(fid);
fid  = fopen([currData,'stripped'],'w');
fprintf(fid,'%s',f);
fclose(fid);


opts = detectImportOptions([currData,'stripped']);
opts.DataLines=6;
opts.SelectedVariableNames = [1,2,3]; 
opts.Delimiter=[' '];

data=readmatrix([currData,'stripped'],opts);
ADV1FYS=data;


currData='interface/0/force.dat'

fid  = fopen(currData,'r');
f=fread(fid,'*char')';
f = strrep(f,'(','');
f = strrep(f,')','');
f = strrep(f,'	',' ');

for i =1:100;

f = strrep(f,'  ',' ');

end
fclose(fid);

fid  = fopen([currData,'stripped.dat'],'w');
fprintf(fid,'%s',f);
fclose(fid);


opts = detectImportOptions([currData,'stripped.dat']);
opts.DataLines=4;
opts.SelectedVariableNames = [1,2,3]; 
opts.Delimiter=[' '];

data=readmatrix([currData,'stripped.dat'],opts);

data=readmatrix(currData,opts);
ForceFYS=data;


currData='interface/0/moment.dat'

fid  = fopen(currData,'r');
f=fread(fid,'*char')';
f = strrep(f,'(','');
f = strrep(f,')','');
f = strrep(f,'	',' ');

for i =1:100;

f = strrep(f,'  ',' ');

end
fclose(fid);

fid  = fopen([currData,'stripped.dat'],'w');
fprintf(fid,'%s',f);
fclose(fid);


opts = detectImportOptions([currData,'stripped.dat']);
opts.DataLines=4;
opts.SelectedVariableNames = [1,2,3]; 
opts.Delimiter=[' '];

data=readmatrix([currData,'stripped.dat'],opts);

data=readmatrix(currData,opts);
MomentFYS=data;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% EVERYTHING ABOVE THIS IS ALL IMPORTING THINGS %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% p1FYS=unique(p1FYS);
% p2FYS=unique(p2FYS);
% p3FYS=unique(p3FYS);
% MomentFYS=unique(MomentFYS);
% ForceFYS=unique(ForceFYS);
% 
% 
% ADV1FYS=unique(ADV1FYS);
% 
% WG1FYS=unique(WG1FYS);
% WG2FYS=unique(WG2FYS);
% WG3FYS=unique(WG3FYS);


figure
hold on
plot(p1FYS)
plot(p2FYS)
plot(p3FYS)
xlabel( ...
    'Time [s]')
ylabel('Pressure [Pa]')
title('Pressure Sensors')
legend('P1', ...
    'P2', ...
    'P3')

figure
hold on
plot(ADV1FYS)
xlabel( ...
    'Time [s]')
ylabel('Velocity [m/s]')
title('Velocity Probe')
legend( ...
    'X','Y','Z')

figure
hold on
plot(WG1FYS(:,1:2))
plot(WG2FYS(:,1:2))
plot(WG3FYS(:,1:2))
xlabel( ...
    'Time [s]')
ylabel('Free Surface Elevation [m]')
title('Wave Gauges')
legend('WG1', ...
    'WG2', ...
    'WG3')

figure
plot(ForceFYS)

xlabel( ...
    'Time [s]')
ylabel('Force [N]')
legend( ...
    'X','Y','Z')
title('FSI Interface Forces')

figure
plot(MomentFYS)

xlabel( ...
    'Time [s]')
ylabel('Moment [N-m]')
legend( ...
    'Mxx','Myy','Mzz')
title('FSI Interface Moments')



function smoothed=customSmooth(x);

smoothed=x;
for i =1:1;
    smoothed=smoothdata(smoothed)
end
end