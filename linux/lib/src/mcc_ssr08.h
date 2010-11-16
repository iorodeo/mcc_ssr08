/******************************************************************************
 * mcc_ssr08.h
 *
 * A simple library for communicating with the Measurement Computing USB-SSR08
 * solid state relay module. Allows you to flash the devices LED and to set the
 * output state of the solid state relays.  
 *
 ******************************************************************************/
#ifndef _MCC_SSR08_H_
#define _MCC_SSR08_H_
#include <sys/types.h>
#include <asm/types.h>
#include <pmd.h>
#include <usb-ssr.h>

#define FAIL 1
#define SUCCESS 0
#define BLINK_DT 4000000

// Function prototypes
int open_device(HIDInterface **hid);
int close_device(HIDInterface **hid);
void blink_LED(HIDInterface *hid);
int set_device_output(HIDInterface *hid, int value);
int define_fail(void);
int define_success(void);

#endif
