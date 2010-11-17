% MCC_SSR08 provides an interface to the Measurement Computing USB-SSR08 solid 
% state relay devices.
%
% Usage: 
%   mcc_ssr08(board_num, command_sting, [value])
% 
% where:
%   board_num      = the installed board ID # as return by daqhwinfo('mcc')
%   command_string = a string specifying the desired command. Allowed command 
%                    strings:
%                    'flashled' for flashing the device's LED
%                    'allhi' for setting all DIO lines to high
%                    'alllo' for setting all DIO lines to low
%                    'setvalue' for setting the DIO lines to a specific value 
%                    given by the third argument value. 
%   value          = third argument required for the 'setvalue' command.
%                    Should be between 0 and 255. The first 8 bits of the 
%                    of the number are used to set the DIO lines.
%
% Examples:
% 
%  mcc_ssr08(0, 'flashled')
%  mcc_ssr08(0, 'allhi')
%  mcc_ssr08(0, 'alllo')
%  mcc_srr08(0, 'setvalue', 122)
%