close all
clear all
clf

%% RAW DATA %%
load PC_DEM.mat
xyz=DEM.xyz;

% remove no data
ind_good=find(xyz(:,3)>-999);
xyz=xyz(ind_good,:);

% %% MAKE GRID %%
xl=min(xyz(:,1));
xh=max(xyz(:,1));

yl=min(xyz(:,2));
yh=max(xyz(:,2));

alpha = -27; % -65;

dx = 1;
dy = 1;

x = [xl:dx:xh];
y = [yl:dy:yh];

[x y] = meshgrid(x,y);

midx=mean(mean(x));
midy=mean(mean(y));

x=x-midx;
y=y-midy;

%% ROTATE GRID %%

R = [cosd(alpha) -sind(alpha); sind(alpha) cosd(alpha)];
b = R*[x(:)'; y(:)'];

xr = b(1,:)';
yr = b(2,:)';

xr = reshape(xr,size(x));
yr = reshape(yr,size(y));

xrg = xr+midx;
yrg = yr+midy;

%% INTERPOLATE DATA %%

F = scatteredInterpolant(xyz(:,1), xyz(:,2), xyz(:,3),'linear','linear');
zrg = F(xrg,yrg);

X = xrg;
Y = yrg;
Z = zrg;

%% EXPORT %%

[mo,no]=size(Z);
dxo=dx/cosd(alpha);
dyo=dy/cosd(alpha);
x=X(1,1)+[0:dxo:(no-1)*dxo]';
y=Y(1,1)+[0:dyo:(mo-1)*dyo]';
h=Z;


% take part for simulation
x1=x(1)+200;
x2=x(end)-200;
y1=3.3296e6+100;
y2=3.3308e6-200;

dxc=dx;
xc=[x1:dxc:x2];
yc=[y1:dxc:y2];

hc=interp2(x,y',h,xc,yc');

x=xc-xc(1);
y=yc-yc(1);
x=x';
y=y';
h=hc;


nx=length(x);
ny=length(y);
% smooth offshore bathy at offshore boundary.  Highly irregular bathy will
% cause waves to scatter at the boundary unphysically
max_depth = min(min(h));  % set depth another offshore boundary to max depth everywhere
max_depth_band=25; % make nearest 25 points all the same depth
h(1:max_depth_band,:)=max_depth;  % for south boundary
max_depth_ramp = 50;  % ramp the depths linearly back to the actual values over 50 points
for i=1:nx
    depth_up = h(max_depth_band+max_depth_ramp,i);
    delta_d = (depth_up-max_depth)/max_depth_ramp;
    for j=max_depth_band+max_depth_ramp:-1:max_depth_band
        h(j,i)=max(max_depth,h(j+1,i)-delta_d);
    end
end



clf
surf(x,y,h)
view(0,90)
shading interp
axis equal
colorbar
caxis([-10 10])
xlabel('Easting (m)')
ylabel('Northing (m)')
pause(.1)

print -djpeg100 bathy.jpg

%*******************************************************************

save celeris_bathy.mat x y h  x1 x2 y1 y2 alpha





