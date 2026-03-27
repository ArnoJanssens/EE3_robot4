
#include "config.h"
#include "mcc_generated_files/system/system.h"

static volatile int8_t currentAct = -1;

void startup_sequence_actuator_on(int8_t i){
    switch(i){
        //turn on all big solenoids 
        case 0: IO_RD0_SetHigh(); break; //block solenoid
        case 1: IO_RD2_SetHigh(); break; //valve
    
    //turn on all small solenoids
        case 2: IO_RC0_SetHigh(); break; // switch led
        case 3: IO_RB5_SetHigh(); break; //laser
    
    //connection to outer PCB
    
        case 4: IO_RD3_SetHigh(); break; //uOutChaser
        case 5: IO_RD5_SetHigh(); break; //uCoutoutofammo
        case 6: IO_RD4_SetHigh(); break; //uCoutBoltHold
        case 7: IO_RD1_SetHigh(); break; //UCoutFout
        case 8:  break; //uCoutLEDBOLTR, now being used as input pin for safety switch
        case 9: IO_RB3_SetHigh(); break; //uCoutLEDMAGR
        default: break;
    }
}

void startup_sequence_actuator_off(int8_t i){
    switch(i){
        //turn on all big solenoids 
        case 0: IO_RD0_SetLow(); break;//block solenoid
        case 1: IO_RD2_SetLow(); break; //valve
    
    //turn on all small solenoids
        case 2: IO_RC0_SetLow(); break; // switch led
        case 3: IO_RB5_SetLow(); break; //laser
    
    //connection to outer PCB
    
        case 4: IO_RD3_SetLow(); break; //uOutChaser
        case 5: IO_RD5_SetLow(); break; //uCoutoutofammo 
        case 6: IO_RD4_SetLow(); break; //uCoutBoltHold
        case 7: IO_RD1_SetLow(); break; //UCoutFout
        case 8: IO_RA4_SetLow(); break; //uCoutLEDBOLTR
        case 9: IO_RB3_SetLow(); break; //uCoutLEDMAGR
        default: break;
    }
}

void startup_sequence_OnTimerInterrupt(void) 
{
    startup_sequence_actuator_off(currentAct);
    currentAct++;
    if (currentAct >= N_ACTUATORS){
        void TMR0_Deinitialize(void);
        TMR0_OverflowCallbackRegister(NULL);
        //laser_set(true); //turn laser on permanently
        return;
        }
    startup_sequence_actuator_on(currentAct);
}

void startup_sequence_Init(void){
    TMR0_Initialize_startup_sequence();
    TMR0_OverflowCallbackRegister(startup_sequence_OnTimerInterrupt);
}