"""
This examples demonstrates how to use the SSR08_Device class to talk to
the USB-SSR08 solid state relay device.

"""
import time
from mcc_ssr08 import SSR08_Device

dev = SSR08_Device()
dev.open()
dev.blink_LED()

for i in range(0,256) + [0]:
    print 'setting value to {0}'.format(i)
    dev.set_output(i)
    time.sleep(0.05)

dev.close()


