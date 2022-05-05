port = 'COM11';

s = serialport(port,9600);

line = fscanf(s);
fprintf(line)