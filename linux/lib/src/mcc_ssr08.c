/******************************************************************************
 * mcc_ssr08.c
 *
 * A simple library for communicating with the Measurement Computing USB-SSR08
 * solid state relay module. 
 * 
 ******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include "mcc_ssr08.h"

/******************************************************************************
 * Function: setDeviceOutput
 *
 * Purpose: sets the output of the USB-SSR08 device based on bits of the given 
 * input value which must be between 0 and 255. 
 *
 ******************************************************************************/
int set_device_output(HIDInterface *hid, int value)
{
    int lo_bits;
    int hi_bits;

    if ((value < 0) || (value > 255)) {
        fprintf(stderr,"value must be between 0 and 255\n");
        return FAIL;
    }

    // Get bits 0-3 and 4-7 from value
    lo_bits = value & 0x0f;
    hi_bits = (value & 0xf0) >> 4;

    // Set output
    usbDOut_USBSSR(hid, (__u8) 2, (__u8) lo_bits);
    usbDOut_USBSSR(hid, (__u8) 3, (__u8) hi_bits);
}

/******************************************************************************
 * Function: blink_LED
 *
 * Purpose: test function, blinks led on device. Sleeps after function call
 * to wait for blinking to stop and device to be ready for other commands
 *
 ******************************************************************************/
void blink_LED(HIDInterface *hid)
{
    // Blink LED
    usbBlink_USBSSR(hid);
    usleep(BLINK_DT);
}

/******************************************************************************
 * Function: open_device
 *
 * Purpose: initializes libhid and sets up the interface to device 
 *
 ******************************************************************************/
int open_device(HIDInterface **hid) 
{
    hid_return ret;
    int interface;

    // Initialize libhid
    ret = hid_init();
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_init failed with return code %d\n", ret);
        return FAIL;
    }

    // Find interface
    interface = PMD_Find_Interface(hid, 0, USBSSR08_PID);
    if (interface < 0) {
        fprintf(stderr, "USB SSR24 or SSR08 not found.\n");
        return FAIL;
    }

    return SUCCESS;
}

/******************************************************************************
 * Function: close_devie
 *
 * Purpose: closes device and cleans up
 *
 ******************************************************************************/
int close_device(HIDInterface **hid)
{
    hid_return ret;

    // Clean up
    ret = hid_close(*hid);
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_close failed with return code %d\n", ret);
        return FAIL;
    }
    hid_delete_HIDInterface(hid);
    ret = hid_cleanup();
    if (ret != HID_RET_SUCCESS) {
        fprintf(stderr, "hid_cleanup failed with return code %d\n", ret);
        return FAIL;
    }
    return SUCCESS;
}


// Functions for getting defines into python using ctypes
int define_fail(void) { return FAIL;};
int define_success(void) {return SUCCESS;}
