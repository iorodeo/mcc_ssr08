function test_mcc_ssr08(board_num)
% TEST_MCC_SSR08 - a simple test function for the mcc_ssr mex file
% interface to the USB-SSR08 solid state relay device. Flashes the LED and
% cycles through all possible output values.
%
% Usage:
% test_mcc_ssr08
%
% Note, this program should not be run when the USB-SSR08 device is
% connected to the Linmot motor controller as unless there are 255 patterns
% stored in the drive it will cause the drive to enter an error state. If
% this happens just cycle the 24V power to the drive.

dt_long = 1.0;
dt_short = 0.02;

fprintf('flashing LED\n');
mcc_ssr08(board_num,'flashled');
pause(dt_long);

fprintf('setting all outputs high\n');
mcc_ssr08(board_num, 'allhi');
pause(dt_long);

fprintf('setting all output low\n');
mcc_ssr08(board_num, 'alllo');
pause(dt_long);

for i = 0:255
    fprintf('setting output to %d\n', i);
    mcc_ssr08(board_num, 'setvalue',i);
    pause(dt_short);
end

fprintf('setting all output low\n');
mcc_ssr08(board_num, 'alllo');