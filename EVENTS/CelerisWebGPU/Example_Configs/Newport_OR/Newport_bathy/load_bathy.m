close all
clear all
clf

deg_m_conv_lat=111123;
deg_m_conv_lon=79462;

load Newport_CentralOregon08_NGDC.mat

diff_lat=diff(lat);
diff_lon=diff(lon);
nx=length(lon);
ny=length(lat);
x=zeros(nx,1);
y=zeros(ny,1);

for i=1:length(diff_lon)
    x(i+1)=x(i)+diff_lon(i)*deg_m_conv_lon;
end
for j=1:length(diff_lat)
    y(j+1)=y(j)+diff_lat(j)*deg_m_conv_lat;
end

h=elevation;

h=h(450:950,900:1160);
x=x(900:1160);
y=y(450:950);

lon=lon(900:1160);
lat=lat(450:950);


% rotate 90 CCW
nx=length(x);
ny=length(y);

% smooth offshore bathy at offshore boundary.  Highly irregular bathy will
% cause waves to scatter at the boundary unphysically
max_depth = min(min(h));  % set depth another offshore boundary to max depth everywhere
max_depth_band=5; % make nearest 25 points all the same depth
h(:,1:max_depth_band)=max_depth;  % for west boundary
max_depth_ramp = 10;  % ramp the depths linearly back to the actual values over 50 points
for j=1:ny
    depth_right = h(j,max_depth_band+max_depth_ramp);
    delta_d = (depth_right-max_depth)/max_depth_ramp;
    for i=max_depth_band+max_depth_ramp:-1:max_depth_band
        h(j,i)=max(max_depth,h(j,i+1)-delta_d);
    end
end



pcolor(x,y,h)
shading interp
colorbar

print -djpeg100 bathy.jpg 

% save for Celeris
x=x'-x(1);
y=y'-y(1);

save celeris_bathy.mat x y h lon lat