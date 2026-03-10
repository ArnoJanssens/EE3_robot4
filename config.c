#include "config.h"
#include "mcc_generated_files/system/system.h"

void resetActuators(void){
    IO_RD0_SetLow(); //block solenoid
    IO_RD2_SetLow(); //valve
    IO_RC0_SetLow(); // switch led
    IO_RB5_SetLow(); //laser    
    IO_RD3_SetLow(); //uOutChaser
    IO_RD5_SetLow(); //uCoutoutofammo
    IO_RD4_SetLow(); //uCoutBoltHold
    IO_RD1_SetLow(); //UCoutFout
    IO_RA4_SetLow(); //uCoutLEDBOLTR
    IO_RB3_SetLow(); //uCoutLEDMAGR
}

void blocking_solenoid_set(bool enable){
    if(enable)  IO_RD0_SetHigh();
    else  IO_RD0_SetLow();
}