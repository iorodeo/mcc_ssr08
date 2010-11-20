function create_test_curve_1
% CREATE_TEST_CURVE - generates a test curve suitable for use in the LinMot
% motor controllers. The curve is a simple there and back cosine curve
% starting from position 230mm, going to position 10mm, and then back to
% position 230. 
%
% Note, the motor must be in positon 230 when this curve is triggered
% otherwise the drive will enter an error state.
%

pos0 = 230;
pos1 = 10;
amp = 0.5*(pos0-pos1);

t = linspace(0,1, 500);
x = amp*cos(2*pi*t) + amp + pos1;

fid = fopen('curve_1_data.csv','w');
for i = 1:length(x)
    fprintf(fid,'%1.4f\n',x(i));
end
fclose(fid);