"""
mcc_ssr08.py

This module provices a simple interface to the Measurement Computing USB-SSR08
solid state relay IO devices. 

Author: Will Dickson, 11/16/2010

"""
import ctypes


class SSR08_Device(object):
    """
    Provides a simple interface to the Measurement Computing USB-SSR08
    solid state relay IO device. 
    """

    def __init__(self):
        self.is_open = False
        self.hid = ctypes.c_void_p() 

    def open(self):
        if self.is_open == True:
            return
        flag = lib.open_device(ctypes.pointer(self.hid))
        if flag == SUCCESS:
            self.is_open = True

    def close(self):
        if self.is_open == False:
            return
        flag = lib.close_device(ctypes.pointer(self.hid))
        if flag == SUCCESS:
            self.is_open = False

    def blink_LED(self):
        if self.is_open == True:
            lib.blink_LED(self.hid)

    def set_output(self, value):
        value = int(value)
        if (value < 0) or (value > 255):
            raise ValueError, 'value must be between 0 and 255'
        flag = lib.set_device_output(self.hid,value)
        if flag == FAIL:
            raise IOError, 'error setting device value'


# ctypes interface
# ------------------------------------------------------------------------
lib = ctypes.cdll.LoadLibrary('libmcc_ssr08.so')

FAIL = lib.define_fail()
SUCCESS = lib.define_success()

# Functions
lib.open_device.restype = ctypes.c_int
lib.open_device.argstype = [ctypes.c_void_p]
lib.close_device.restype = ctypes.c_int
lib.close_device.argstype = [ctypes.c_void_p]
lib.blink_LED.argstype = [ctypes.c_void_p]
lib.set_device_output.restype = ctypes.c_int
lib.set_device_output.argstype = [ctypes.c_void_p, ctypes.c_int]



