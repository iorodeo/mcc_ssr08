function test_mcc_ssr08(board_num)
% TEST_MCC_SSR08 - a simple test function for the mcc_ssr mex file
% interface to the USB-SSR08 solid state relay device.
%
% Usage:
% test_mcc_ssr08

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