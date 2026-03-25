#include "config.h"
#include "safety.h"
#include "mcc_generated_files/system/system.h"
void reset(){
    SYSTEM_Initialize();
    resetActuators();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    safety_initialize();
    
}
void resetActuators(void){
    IO_RD0_SetLow(); //block solenoid
    IO_RD2_SetLow(); //valve
    IO_RC0_SetLow(); // switch led
    IO_RB5_SetLow(); //laser    
    IO_RD3_SetLow(); //uOutChaser
    IO_RD5_SetLow(); //uCoutoutofammo
    IO_RD4_SetLow(); //uCoutBoltHold
    IO_RD1_SetLow(); //UCoutFout
    IO_RB3_SetLow(); //uCoutLEDMAGR
    IO_RD6_SetLow(); //disableReleaseClick
    IO_RD7_SetLow(); //disablePullClick
}

void blocking_solenoid_set(bool enable){
    if(enable)  IO_RD0_SetHigh();
    else  IO_RD0_SetLow();
}

void cylinder_set(bool extended){
    if(extended) IO_RD2_SetHigh();
    else IO_RD2_SetLow();
}

void error_lights(bool on){
    if(on){
        IO_RD1_SetHigh();
    }
    else IO_RD1_SetLow();
}

void bolt_release_led(bool on){
    if(on){
        IO_RD4_SetHigh();
    }
    else{
        IO_RD4_SetLow();
    }
        
}

