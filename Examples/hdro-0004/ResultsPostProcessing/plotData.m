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

currData='PressureProbe4/0/p'
opts = detectImportOptions(currData);
opts.DataLines=4;
opts.SelectedVariableNames = [1,2]; 
opts.Delimiter='  ';

data=readmatrix(currData,opts);
p4FYS=data;


currData='WaveGauge1/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG1FYS=data;

currData='WaveGauge2/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG2FYS=data;

currData='WaveGauge3/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG3FYS=data;

currData='WaveGauge4front/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG4FYS=data;

currData='WaveGauge5back/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG5FYS=data;

currData='WaveGauge6left/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG6FYS=data;

currData='WaveGauge7right/0/height.dat'
opts = detectImportOptions(currData);
opts.DataLines=1;
opts.SelectedVariableNames = [1,2,3]; 
% opts.Delimiter=' ';

data=readmatrix(currData,opts);
WG7FYS=data;

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
opts.SelectedVariableNames = [1,2,3,4]; 
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
opts.SelectedVariableNames = [1,2,3,4]; 
% opts.Delimiter=[' '];

data=readmatrix([currData,'stripped.dat'],opts);

% data=readmatrix(currData,opts);
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
opts.SelectedVariableNames = [1,2,3,4]; 
% opts.Delimiter=[' '];

data=readmatrix([currData,'stripped.dat'],opts);

% data=readmatrix(currData,opts);
MomentFYS=data;





currData='storyForces/0/forceBin.dat'

fid = fopen(currData);
tline = fgetl(fid);
lineCounter = 1;
while ischar(tline)
    disp(tline)
    if contains(tline,'# bins        : ')
        break;
    end
    % Read next line
    tline = fgetl(fid);
    lineCounter = lineCounter + 1;
end
fclose(fid);

nBins=str2num(strrep(tline,'# bins        : ',''));


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
opts.DataLines=13;
colList=[1];
for i=1:nBins;
    colList(end+1:end+3)=[4+(((i-1)*9)-2),4+(((i-1)*9)-1),4+(((i-1)*9))]
end
% storyForces=data(:,colList);
opts.SelectedVariableNames = colList; 
opts.Delimiter=[' '];

data=readmatrix([currData,'stripped.dat'],opts);

storyForces=data;

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
plot(p1FYS(:,1),p1FYS(:,2))
plot(p2FYS(:,1),p2FYS(:,2))
plot(p3FYS(:,1),p3FYS(:,2))
plot(p4FYS(:,1),p4FYS(:,2))
xlabel( ...
    'Time [s]')
ylabel('Pressure [Pa]')
title('Pressure Sensors')
legend('P1', ...
    'P2', ...
    'P3', ...
    'P4')

figure
hold on
plot(ADV1FYS(:,1),ADV1FYS(:,2))
plot(ADV1FYS(:,1),ADV1FYS(:,3))
plot(ADV1FYS(:,1),ADV1FYS(:,4))


xlabel( ...
    'Time [s]')
ylabel('Velocity [m/s]')
title('Velocity Probe')
legend( ...
    'X','Y','Z')

figure
hold on
plot(WG1FYS(:,1),WG1FYS(:,2))
plot(WG2FYS(:,1),WG2FYS(:,2))
plot(WG3FYS(:,1),WG3FYS(:,2))
plot(WG4FYS(:,1),WG4FYS(:,2))
plot(WG5FYS(:,1),WG5FYS(:,2))
plot(WG6FYS(:,1),WG6FYS(:,2))
plot(WG7FYS(:,1),WG7FYS(:,2))
xlabel( ...
    'Time [s]')
ylabel('Free Surface Elevation [m]')
title('Wave Gauges')
legend('WG1', ...
    'WG2', ...
    'WG3', ...
    'WG4', ...
    'WG5', ...
    'WG6', ...
    'WG7')

figure
hold on
plot(ForceFYS(:,1),ForceFYS(:,2))
plot(ForceFYS(:,1),ForceFYS(:,3))
plot(ForceFYS(:,1),ForceFYS(:,4))

xlabel( ...
    'Time [s]')
ylabel('Force [N]')
legend( ...
    'X','Y','Z')
title('FSI Interface Forces')

figure
hold on
plot(MomentFYS(:,1),MomentFYS(:,2))
plot(MomentFYS(:,1),MomentFYS(:,3))
plot(MomentFYS(:,1),MomentFYS(:,4))

xlabel( ...
    'Time [s]')
ylabel('Moment [N-m]')
legend( ...
    'Mxx','Myy','Mzz')
title('FSI Interface Moments')




figure
hold on
for i=1:nBins;
    subplot(3,1,1)
    hold on
plot(storyForces(:,1),storyForces(:,4+((i-1)*3 -2)),'DisplayName',['Story ',num2str(i),' X Force']);
subplot(3,1,2)
    hold on
plot(storyForces(:,1),storyForces(:,4+((i-1)*3 -1)),'DisplayName',['Story ',num2str(i),' Y Force']);
subplot(3,1,3)
    hold on
plot(storyForces(:,1),storyForces(:,4+((i-1)*3 )),'DisplayName',['Story ',num2str(i),' Z Force']);
end


subplot(3,1,1)
xlabel( ...
    'Time [s]')
ylabel('Force [N]')
legend()

subplot(3,1,2)
xlabel( ...
    'Time [s]')
ylabel('Force [N]')
legend()
subplot(3,1,3)

xlabel( ...
    'Time [s]')
ylabel('Force [N]')
legend()
sgtitle('Story Forces')




function smoothed=customSmooth(x);

smoothed=x;
for i =1:1;
    smoothed=smoothdata(smoothed)
end
end