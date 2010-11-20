function create_test_curve_2
%CREATE_TEST_CURVE_2 - generates a test curve suitable for use in the LinMot
% motor controllers.
%
% 
% Note, the motor must be in positon 230 when this curve is triggered
% otherwise the drive will enter an error state.
%

pos0 = 230;
pos1 = 10;

% Create Curve
t = linspace(0,1,500);
x = cos(2*pi*t) + 0.6*cos(6*pi*t);

% Shift so that it goes between 0 and 1
x = (x - min(x))/(max(x) - min(x));

% Scale and shift so that is goes from pos0 to pos1 to pos0
x = (pos0 - pos1)*x + pos1;

% Write to csv file
fid = fopen('curve_2_data.csv','w');
for i = 1:length(x)
    fprintf(fid,'%1.4f\n',x(i));
end
fclose(fid);