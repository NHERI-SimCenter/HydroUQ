clc
clear

%filename = 'norcal_a_s2_c.txt'; %a1
%filename = 'norcal_b4_s_c.txt'; %b1
filename = 'ventura_1_3_c_corr.txt'; %c

%filename is the name of a MOST bathymetry file
%
% B is the bathymetry matrix (Positive for downward)
% X is the vector of X coordinates
% Y is the vector of Y coordinates

fid=fopen(filename,'r');

N=fscanf(fid,'%d',2);

X=fscanf(fid,'%f',N(1));
Y=fscanf(fid,'%f',N(2));

B=zeros(N(2),N(1));
for k=1:N(2)
    B(k,:)=fscanf(fid,'%f',N(1)).';
end

sx=510;
sy=190;

ex=750;
ey=447;
B=B(sy:ey,sx:ex);
X=X(sx:ex);
Y=Y(sy:ey);

h=-flipud(B);

[ny,nx]=size(h);
dx=10;
x=[0:dx:(nx-1)*dx]';
y=[0:dx:(ny-1)*dx]';

for i=1:nx
    if x(i)<400
        for j=1:ny
            if h(j,i)<-15
                h(j,i)=-15;
            end
        end
    end
end
for i=1:nx
    for j=1:ny
        if h(j,i)>5
            h(j,i)=5;
        end
    end
end


%********************************************************************
%% plot the data
clf
clear hold
%x=x/1000;
%y=y/1000;

surf(x,y,h)
%axis equal
axis([-Inf Inf -Inf Inf -100 100])
%hold on
view(0,90)
grid off
shading interp
%caxis([min(min(h)) 5])
colorbar
xlabel('x (m)')
ylabel('y (m)')
print -djpeg100 bathy.jpg

%*******************************************************************

% save for Celeris
x=x';
y=y;

save celeris_bathy.mat x y h
