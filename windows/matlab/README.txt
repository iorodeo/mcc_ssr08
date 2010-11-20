mcc_ssr08 - mex file interface to the Measurement computing USB-SSR08 solid
state relay devices.

For installation instructions see INSTALL.txt in the windows/matlab/ directory.

Usage: 
  mcc_ssr08(board_num, command_sting, [value])

where:
  board_num      = the installed board ID # as return by daqhwinfo('mcc')
  command_string = a string specifying the desired command. Allowed command 
                   strings:
                   'flashled' for flashing the device's LED
                   'allhi' for setting all DIO lines to high
                   'alllo' for setting all DIO lines to low
                   'setvalue' for setting the DIO lines to a specific value 
                   given by the third argument value. 
  value          = third argument required for the 'setvalue' command.
                   Should be between 0 and 255. The first 8 bits of the 
                   of the number are used to set the DIO lines.

Examples:

 mcc_ssr08(0, 'flashled')
 mcc_ssr08(0, 'allhi')
 mcc_ssr08(0, 'alllo')
 mcc_srr08(0, 'setvalue', 122)

Note, the first time the function is called (during a Matlab session) it is a bit slow - as 
the library is being loaded. Subsequent calls are very fast. For this reason programs using
the mcc_ssr08 function in time critical section might want to call it at least once in some
non-critical section (like an initialization routine). 

Also note the library can always be cleared from memory using "mex clear". 

Some example function using the mcc_ssr08 command can be found in the examples
directory.  There are also two functions giving examples of how to generate
curves suitable for downloading into the LinMot E1100 motor controllers.

mcc_ssr08 may be freely distributed and modified in accordance with the Apache
2.0  License.

