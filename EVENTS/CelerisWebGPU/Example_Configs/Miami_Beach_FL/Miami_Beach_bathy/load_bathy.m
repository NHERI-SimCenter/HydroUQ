%
%
%

clear; close all
tic
load NorthMiamiBeach.txt;
z=NorthMiamiBeach(:,3)/3.28;
m=1309;
n=689;
ds=3;

h=reshape(z,[n,m])';

x=[0:ds:(n-1)*ds];
y=[0:ds:(m-1)*ds];

% smooth offshore bathy at offshore boundary.  Highly irregular bathy will
% cause waves to scatter at the boundary unphysically
max_depth = min(min(h));  % set depth another offshore boundary to max depth everywhere
max_depth_band=25; % make nearest 25 points all the same depth
h(:,end-max_depth_band:end)=max_depth;  % for east boundary
max_depth_ramp = 50;  % ramp the depths linearly back to the actual values over 50 points
for j=1:m
    depth_left = h(j,end-max_depth_band-max_depth_ramp);
    delta_d = (depth_left-max_depth)/max_depth_ramp;
    for i=n-max_depth_band-max_depth_ramp:n-max_depth_band
        h(j,i)=max(max_depth,h(j,i-1)-delta_d);
    end
end


clf
surf(x,y,h)
view(0,90)
shading interp
grid off
colorbar
%caxis([-.2 .0])
xlabel('X (m)')
ylabel('y (m)')
pause(.1)
axis equal
print -djpeg100 bathy.jpg

%*******************************************************************

% save for Celeris
save celeris_bathy.mat x y h


