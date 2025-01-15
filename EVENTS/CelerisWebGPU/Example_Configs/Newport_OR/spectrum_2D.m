function spectrum_2D(Hs_o,Tp,Thetap,h)

% function file to create random wave input files (directional, TMA) for COULWAVE
%Hs_o=2.; %Hmo at source depth in m
%Tp=12; % peak period in s
%Thetap=0;  %mean wave direction, relative to source line
gamma_s=3.3;  % frequency spreading factor for TMA spectrum
spread_o=50;  % direction spreading factor
%h=10;  % depth at source region in m
del_f=0.005; % frequency increment, time series will repeat at 1/del_f seconds
del_t=5;  % direction increment
%%%%%%End User change section%%%%%%%%%%

spectrum_type=1;  %0=input, 1=TMA
f_peak=1/Tp;
Hs=Hs_o;
g=9.81;		% gravity
Hs=min([Hs,h*0.5]);  % limit wave height to 1/2 of water depth at generation
Hs_old=Hs;

if spectrum_type==0
    load spec.dat
    f=spec(:,1);
    f_peak=0.1;
    del_f=f(2)-f(1);
    E=spec(:,2);
elseif spectrum_type==1
   % Shalllow water TMA spectrum
    
    beta=0.0624/(0.23+0.033*gamma_s-0.185*(1.9+gamma_s)^-1);
    
    % Calculate Energy Spectrum to Very Large Limits
    f_start=max(del_f,f_peak-5*del_f);
    f_end=f_peak+5*del_f;
    
    f=[f_start:del_f:f_end];
    for i=1:length(f)
       omega_h=2*3.1415*f(i)*sqrt(h/g);
       if omega_h>2
          phiK=1;
       elseif omega_h<1
          phiK=0.5*omega_h;
       else
          phiK=1-0.5*(2-omega_h)^2;
       end
       
        if f(i)<=f_peak
            sigma=0.07;
        else
            sigma=0.09;
        end
        
        frat=f(i)/f_peak;
         
        E(i)=beta*Hs^2/(f(i)*frat^4)*exp(-1.25/frat^4)*gamma_s^(exp(-(frat-1)^2/(2*sigma^2)));  % energy density
    end
    
    % Directional Spectrum to Very Large Limits
    theta=[-20+Thetap:del_t:20+Thetap];
    for i=1:length(f)
       theta_peak(i)=Thetap;  % (degrees) Input some function here to determine the mean wave direction as a function of frequency
       f_rat=f(i)/f_peak; 
       
       if f_rat<1
          spread=spread_o*f_rat^5;
       else
          spread=spread_o*f_rat^-2.5;
       end
       
%       spread=spread_o;
       
       beta_s=2^(2*spread-1)/3.1415*( gamma(spread+1) )^2/gamma(2*spread+1);
       
       for j=1:length(theta)
          D(i,j)=beta_s*cos(0.5*( (theta(j)-theta_peak(i))*3.1415/180 ))^(2*spread) ;  % Directional function
       end
    end   
    
    for i=1:length(f)
       sum=0;
       for j=1:length(theta)
          sum=sum+D(i,j);  % Directional Energy Density function
       end
       D(i,:)=D(i,:)/sum;
    end
    
    
    for i=1:length(f)
       for j=1:length(theta)
          E_D(i,j)=E(i)*D(i,j);  % Directional Energy Density function
       end
    end
  
end

Hmo = 0;

for i=1:length(f)
   for j=1:length(theta)
      if i==1
         del_f=(f(2)-f(1));
      elseif i==length(f)
         del_f=(f(length(f))-f(length(f)-1));
      else
         del_f=(f(i+1)-f(i))/2.+(f(i)-f(i-1))/2.;
      end
      Hmo = Hmo + E_D(i,j)*del_f;
   end
end

Hmo_full_spectrum = sqrt(Hmo)*4.004;
E_D=E_D*(Hs_o/Hmo_full_spectrum)^2.;

% disp(['Input ',' Depth-Limited ',' Cut Spectrum'])
% disp([Hs_o, Hs, Hmo_full_spectrum])

% Truncate ends of spectrum at values of 1% of the max
trunc=0.01;

%DO NOT CHANGE ANYTHING BELOW THIS LINE
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

j=round(length(theta)/2);

if Hmo==0
    f_num=f_peak;
    E_num=0;
    amp_max=0;
    count=1;
else
    max_E=max(E_D(:,j));
    min_E=trunc*max_E;
    count=0;
    for i=1:length(f)
        if E_D(i,j)>min_E
            count=count+1;
            f_num(count)=f(i);
            E_D_num(count,:)=E_D(i,:);
        end
    end
end



fileID = fopen('waves.txt','w');
line1='\n';
line2=['[NumberOfWaves] ' num2str(count*length(theta)) '\n'];
line3='=================================\n';

for i=1:3
    eval(['cline = line' num2str(i) ';'])
    fprintf(fileID,cline);	
end

Hmo_truncated_spectrum=0;
cur_ind=0;
for i=1:count
   if i==1
      del_f=(f(2)-f(1));
   elseif i==count
      del_f=(f(count)-f(count-1));
   else
      del_f=(f(i+1)-f(i))/2.+(f(i)-f(i-1))/2.;
   end

   for j=1:length(theta) 
      amp(i,j)=sqrt(2*E_D_num(i,j)*del_f);
      cur_ind=cur_ind+1;
      file_data(cur_ind,1)=amp(i,j);
      file_data(cur_ind,2)=1/f_num(i);
      file_data(cur_ind,3)=theta(j)*3.1415/180;
      file_data(cur_ind,4)=rand*2*3.1415;
      cline=[num2str(file_data(cur_ind,:)) '\n'];
      fprintf(fileID,cline);	
   end 
end


    
fclose(fileID);


figure(3)
clf
subplot(2,1,1), plot(f_num,E_D_num(:,round(length(theta)/2)));
ylabel('Energy (m^2s)')
xlabel('Frequency (Hz)')
title(['Truncated Energy Spectrum - Truncated at ',num2str(trunc*100),'% of Peak Energy'])
subplot(2,1,2), pcolor(f_num,theta,amp')
shading interp
title(['2-D Amplitude Spectrum Derived From Above With \Deltaf= ',num2str(del_f),' Hz'])
colorbar
ylabel(['Dir Degrees'])
xlabel(['Frequency'])


