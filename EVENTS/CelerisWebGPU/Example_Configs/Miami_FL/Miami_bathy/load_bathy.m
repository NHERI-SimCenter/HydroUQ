close all
clf

load Miami_Beach_modified.txt
h=Miami_Beach_modified;

[ny,nx]=size(h);
ds=3;
x=[0:ds:ds*(nx-1)];
y=[0:ds:ds*(ny-1)];
% smooth offshore bathy at offshore boundary.  Highly irregular bathy will
% cause waves to scatter at the boundary unphysically
max_depth = min(min(h));  % set depth another offshore boundary to max depth everywhere
max_depth_band=25; % make nearest 25 points all the same depth
h(:,end-max_depth_band:end)=max_depth;  % for east boundary
max_depth_ramp = 50;  % ramp the depths linearly back to the actual values over 50 points
for j=1:ny
    depth_left = h(j,end-max_depth_band-max_depth_ramp);
    delta_d = (depth_left-max_depth)/max_depth_ramp;
    for i=nx-max_depth_band-max_depth_ramp:nx-max_depth_band
        h(j,i)=max(max_depth,h(j,i-1)-delta_d);
    end
end

pcolor(x,y,h)
shading interp
colorbar

print -djpeg100 bathy.jpg 

% save for Celeris
x=x'-x(1);
y=y'-y(1);

save celeris_bathy.mat x y h