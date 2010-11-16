/******************************************************************************
 * test_mcc_ssr08.c
 *
 * A simple test function which demostrates how to talk with the Measurement
 * Computing USB-SSR08 solid state relay module.
 *
 ******************************************************************************/
#include <stdio.h>
#include "mcc_ssr08.h"

#define START_VALUE 0
#define STOP_VALUE  255 
#define SET_VALUE_DT 100000

int main(int argc, char *argv[])
{
    int i;
    int rval;
    HIDInterface*  hid = 0x0;

    // Open device
    rval = open_device(&hid);
    if (rval != SUCCESS) {
        fprintf(stderr, "unable to open device\n");
        exit(-1);
    }

    blink_LED(hid);

    // Set device values
    for (i = START_VALUE; i<=STOP_VALUE; i++) {
        printf("setting output to: %d\n", i);
        set_device_output(hid,i);
        usleep(SET_VALUE_DT);
    }

    // Close device
    rval = close_device(&hid);
    if (rval != SUCCESS) {
        fprintf(stderr, "err closing device\n");
        exit(-1);
    }

    return 0;
}
