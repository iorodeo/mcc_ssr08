function build_mcc_ssr08
% BUILD_MCC_SSR08 - compiles the mcc_ssr08 mex file shared library. 
%
% Usage: 
% build_mcc_ssr08
%
mex -I'C:\Users\Public\Documents\Measurement Computing\DAQ\C'  -L'C:\Users\Public\Documents\Measurement Computing\DAQ\C'  mcc_ssr08.c -L.\ -lcbw32
