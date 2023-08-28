//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "pc_serial_com.h"

#include "irrigation_timer.h"
#include "irrigation_control.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

UnbufferedSerial uartUsb(USBTX, USBRX, 115200);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void pcSerialComInit()
{
}

void pcSerialComUpdate()
{
    char str[100] = "";

    irrigationControlStatus_t irrigationControlStatusLocalCopy;
    irrigationControlStatusLocalCopy = irrigationControlRead();

    irrigationTimer_t irrigationTimerLocalCopy;
    irrigationTimerLocalCopy = irrigationTimerRead();

    if ( (irrigationControlStatusLocalCopy.irrigationState ==
        PROGRAMMED_MODE_WAITING_TO_IRRIGATE ) && 
          ( irrigationTimerLocalCopy.waitedTime % 10 == 0) ) {

        sprintf ( str, "Waited Time: %02d hours\r\n",
                    irrigationTimerLocalCopy.waitedTime / 10 );
        uartUsb.write( str, strlen(str) );
    }    
    
    if ( (irrigationControlStatusLocalCopy.irrigationState == 
        PROGRAMMED_MODE_IRRIGATING) && 
          ( irrigationTimerLocalCopy.irrigatedTime % 10 == 0) ) {

        sprintf ( str, "Irrigated Time: %02d seconds\r\n",
            irrigationTimerLocalCopy.irrigatedTime / 10);
        uartUsb.write( str, strlen(str) );
    }
}

void pcSerialComRead()
{
}

//=====[Implementations of private functions]==================================