%Ref https://www.mathworks.com/matlabcentral/answers/80833-simple-matlab-arduino-serial-communication

clear
clc

%instrfind(); show closed and open ports
s = serialport("COM11",9600);

figure (1)
clf

a = 1;
n=1;
while(a)

    tline = readline(s); % scan one line from the serial 
    C = textscan(tline,'%f'); % extract numeric values 
    
    % assign coordinate data and plot in 3D
    C = transpose(C{:});

    x(n) = C(1);
    y(n) = C(2);
    z(n) = C(3);
    plot3(x,y,z,'.')
    pause(0.02)
    n = n+1;
    if n ==360
        a =0;
        clear s;
    end
end

%fclose(s)