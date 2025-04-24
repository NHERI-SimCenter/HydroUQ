clf
clear all

fid(1)=fopen('seaside_matrix.bin', 'r');
dum=fread(fid(1),1,'int32');
m=fread(fid(1),1,'int32');
n=fread(fid(1),1,'int32');
x=fread(fid(1),m,'float32');
y=fread(fid(1),n,'float32');
z=fread(fid(1),[m,n],'float32');
fclose all;

dx=x(2)-x(1);
xmax=x(m);
xmin=x(1);

m_new=round( (xmax+0)/dx );

x_new(m_new)=xmax;
for i=m_new-1:-1:1
   x_new(i)=x_new(i+1)-dx;
end

h_new=zeros(m_new,n);
count=0;
for i=m_new:-1:1
   if x_new(i)>=32.5
      count=count+1;
      h_new(i,:)=z(m-count+1,:);
   elseif x_new(i)>=17.5
      h_new(i,:)=h_new(i+1,:)-dx/30;     
   elseif x_new(i)>=10.
      h_new(i,:)=h_new(i+1,:)-dx/15;
   else
      h_new(i,:)=h_new(i+1,:);   
   end
end

depth=0.75;
h=(h_new-depth)';
x=0;
x=x_new';
y=y-y(1);

%% plot the data

figure(1)
pcolor(x,y,h)
shading interp
axis equal
title('Bathy/Topo DEM')
print -djpeg100 DEM.jpg

save celeris_bathy.mat x y h







