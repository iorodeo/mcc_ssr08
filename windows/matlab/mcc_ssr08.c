/******************************************************************************
 * mcc_ssr08.c
 *
 * Provides a mex file shared library interface for controlling the USB-SSR08
 * solid state relay module interface device.  
 *
 * Usage:
 *
 * mcc_ssr08(boardNum, 'flashled')          - flashes the led on the device
 * mcc_ssr08(boardNum, 'allhi')             - sets all dio lines high 
 * mcc_ssr08(boardNum, 'alllo')             - sets all dio lines low
 * mcc_ssr08(boardNum, 'setvalue', value)   - sets dio lines based on the bits in 
 *                                            value where value is a number between 
 *                                            0 and 256. Note, value is converted 
 *                                            to an integer. 
 *
 * Revision History:
 *
 * Will Dickson, IO Rodeo Inc., 11/02/2010  - Original Version
 *
 ******************************************************************************/
#include <stdio.h>
#include "cbw.h"
#include "mex.h"

// Definitions 
#define CMD_MAX_LEN  100 // Maximum allowed length of the command string
#define ERR_MSG_LEN  100 // Length of error message strings
#define ALL_LO_VALUE 0   // Value for setting all lines low
#define ALL_HI_VALUE 255 // Value for setting all lines high

// Command ids
#define CMD_ID_FLASH_LED 0
#define CMD_ID_ALL_LO    1
#define CMD_ID_ALL_HI    2
#define CMD_ID_SET_VALUE 3

// Function prototype 
int getBoardNum(int nrhs, const mxArray *prhs[]);
int getCmdId(int nrhs, const mxArray *prhs[]);
int getOutValue(int nrhs, const mxArray *prhs[]);
void flashLED(int boardNum);
void setDeviceOutput(int outValue, int boardNum);

/******************************************************************************
 * Function: mexFunction
 *
 * Purpose: entry point to the SSR08 mex file shared library. 
 *
 * Arguments:
 *
 * nlhs = # of left hand arguments, or size of plhs array
 * plhs = array of left hand output arguments
 * nrhs = # of right hand arguments, or size of prhs array
 * prhs = array of right hand input arguments.
 *
 ******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    int cmdId;
    int ULStat;
    int boardNum;
    int outValue;
    float revLevel = (float)CURRENTREVNUM;

    // Check that there are no output arguments
    if (nlhs != 0) {
        mexErrMsgIdAndTxt("MCC_SSR08:nlhs", "too many output arguments, nlhs must be 0\n");
    }

    // Check number of input arguments
    if (nrhs < 2) {
        mexErrMsgIdAndTxt("MCC_SSR08:nrhs","too few input aruments - must be either 2 or 3\n");
    }
    if (nrhs > 3) {
        mexErrMsgIdAndTxt("MCC_SSR08:nrhs", "too many input arguments - must be either 2 or 3\n");
    }

    // Get board number
    boardNum = getBoardNum(nrhs,prhs);

    // Get the command string (first argument)
    cmdId = getCmdId(nrhs,prhs);

    // Declare UL Revision Level
    ULStat = cbDeclareRevision(&revLevel);

    // Perform action based on command Id
    switch (cmdId) {

        case CMD_ID_FLASH_LED:
            flashLED(boardNum);
            break;

        case CMD_ID_ALL_LO:
            // Set all SSR outputs low
            setDeviceOutput(ALL_LO_VALUE,boardNum);
            break;

        case CMD_ID_ALL_HI:
            // Set all SSR output high
            setDeviceOutput(ALL_HI_VALUE,boardNum);
            break;

        case CMD_ID_SET_VALUE:
            // General set value function
            outValue = getOutValue(nrhs, prhs);
            setDeviceOutput(outValue, boardNum);
            break;

        default:
            //  We should not be here
            mexErrMsgIdAndTxt("MCC_SSR08:cmdId", "unknown command id\n");
            break;
    }
    return;
}

/******************************************************************************
 * Function: getBoardNum
 *
 * Purose: returns the first argument passed to the mex program - the board ID.
 *
 *******************************************************************************/
int getBoardNum(int nrhs, const mxArray *prhs[]) 
{
    int boardNum = 0;
    size_t m,n; // number of rows and columns in prhs[0] matrix
    double *boardNumDblPr;

    // Check that it is a number
    if (!mxIsDouble(prhs[0])) {
        mexErrMsgIdAndTxt("MCC_SSR08:getBoardNum:argType", "1st argument of incorrect type - must be a number\n");
    }

    // Check that it is of the correct shape, 1x1 
    m = mxGetM(prhs[0]);
    n = mxGetN(prhs[0]);
    if (!((m==1) && (n==1))) {
        mexErrMsgIdAndTxt("MCC_SSR08:getBoardNum:argType", "1st argument must be 1x1 array\n");
    }
    // Get value as double and convert it to an integer
    boardNumDblPr = mxGetPr(prhs[0]);
    boardNum = (int) (*boardNumDblPr);

    if (boardNum < 0) {
        mexErrMsgIdAndTxt("MCC_SSR08:getBoardNum:range", "1st argument must be >=0\n");
    }
    
    return boardNum;
}

/******************************************************************************
 * Function: getCmdId
 *
 * Purpose: returns  the second argument passed to the mex program - the command
 * string. Checks to ensure that it is a character array and converts to a C
 * string and then to the command id number. 
 *
 ******************************************************************************/
int getCmdId(int nrhs, const mxArray *prhs[]) 
{ 
    int retVal;
    int cmdId;
    char cmdStr[CMD_MAX_LEN]; 
    char errMsg[ERR_MSG_LEN];


    // Get first input argument 
    if (!mxIsChar(prhs[1])) { 
        mexErrMsgIdAndTxt("MCC_SSR08:notChar", "2nd argument must be character array\n");
    }
    retVal = mxGetString(prhs[1], cmdStr, CMD_MAX_LEN);
    if (retVal !=0 ) {
        mexErrMsgIdAndTxt("MCC_SSR08:getString", "unable to return command string\n");
    }

    // Convert command string to command id
    if (_strcmpi(cmdStr, "flashled") == 0) {
        cmdId = CMD_ID_FLASH_LED; 
    }
    else if (_strcmpi(cmdStr, "alllo") == 0) {
        cmdId = CMD_ID_ALL_LO;
    }
    else if (_strcmpi(cmdStr, "allhi") == 0) {
        cmdId = CMD_ID_ALL_HI;
    }
    else if (_strcmpi(cmdStr, "setvalue") == 0) {
        cmdId = CMD_ID_SET_VALUE;
    }
    else {
        // Error - unknown command string.
        _snprintf(errMsg, ERR_MSG_LEN, "unknown command string '%s'\n", cmdStr);
        mexErrMsgIdAndTxt("MCC_SSR08:cmdStr", errMsg); 
    }
    return cmdId;
}


/******************************************************************************
 * Function: getOutValue 
 *
 * Purpose: returns the third argument passed to the mex program, the desired 
 * output value, as an integer.
 *
 * ****************************************************************************/
int getOutValue(int nrhs, const mxArray *prhs[]) 
{ 
    int outValue = 0;
    size_t m,n; // number of rows and columns in prhs[0] matrix
    double *outValueDblPr;

    // Check that there is a second argument 
    if (nrhs != 3) {
        mexErrMsgIdAndTxt("MCC_SSR08:setValue:rhs", "three arguments are required for SetValue command\n");
    }

    // Check that it is a number
    if (!mxIsDouble(prhs[2])) {
        mexErrMsgIdAndTxt("MCC_SSR08:setValue:argType", "3rd argument of incorrect type - must be a number\n");
    }

    // Check that it is of the correct shape, 1x1 
    m = mxGetM(prhs[2]);
    n = mxGetN(prhs[2]);
    if (!((m==1) && (n==1))) {
        mexErrMsgIdAndTxt("MCC_SSR08:setValue:argType", "3rd argument must be 1x1 array\n");
    }

    // Get value as double and convert it to an integer
    outValueDblPr = mxGetPr(prhs[2]);
    outValue = (int) (*outValueDblPr);
    
    return outValue;
}

/******************************************************************************
 * Function: flashLED
 *
 * Purpose: flashes the led on the USB-SSR08 device given the board number.
 *
 ******************************************************************************/
void flashLED(int boardNum)
{ 
    int errCode;
    char errMsg[ERRSTRLEN];

    // Flash LED
    errCode = cbFlashLED(boardNum);
    if (errCode != 0) {
        cbGetErrMsg(errCode,errMsg);
        mexErrMsgIdAndTxt("MCC_SSR08:cbFlashLEDErr", "unable to flash device: %s",errMsg);
    }
    return;
}

/******************************************************************************
 * Function: setDeviceOutput
 *
 * Purpose: sets the output value on the USB-SSR08 solid state relay device base
 * on the bits in the input integer outValue.
 *
 ******************************************************************************/
void setDeviceOutput(int outValue, int boardNum)
{
    int loBits;
    int hiBits;
    int loBitsErrCode;
    int hiBitsErrCode;
    char errMsg[ERRSTRLEN];

    // Check that outValue is between 0 and 255
    if (outValue < 0) {
        mexErrMsgIdAndTxt("MCC_SSR08:outValue:range", "outValue must be > 0\n"); 
    }
    if (outValue > 255) {
        mexErrMsgIdAndTxt("MCC_SSR08:outValue:range", "outValue must be < 256\n");
    }

    // Get lower and upper 4 bits
    loBits = outValue & 0x0f;
    hiBits = (outValue & 0xf0) >> 4;

    // Set outputs on USB-SSR08
    loBitsErrCode = cbDOut(boardNum, FIRSTPORTCL, loBits);
    hiBitsErrCode = cbDOut(boardNum, FIRSTPORTCH, hiBits);

    // Check error codes
    if (loBitsErrCode != 0) {
        cbGetErrMsg(loBitsErrCode,errMsg);
        mexErrMsgIdAndTxt("MCC_SSR08:cbDOutErr", "unable to set output: %s",errMsg);
    }
    if (hiBitsErrCode != 0) {
        cbGetErrMsg(loBitsErrCode,errMsg);
        mexErrMsgIdAndTxt("MCC_SSR08:cbDOutErr", "unable to set output: %s",errMsg);
    }

    return;
}
