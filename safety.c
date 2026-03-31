#include "safety.h"
#include "config.h"
#include "mcc_generated_files/system/interrupt.h"
#include "mcc_generated_files/system/pins.h"
#include "mcc_generated_files/system/system.h"

volatile int8_t safetyStatus = MODE_ERROR;


void interrupt_routine_trigger_1(void){
    cylinder_set(true);
    bolt_release_led(true);
    IO_RA3_SetInterruptHandler(interrupt_routine_LS2_shooting); //LS1
    INT1_SetInterruptHandler(NULL);
}

void interrupt_routine_trigger_A(void){
    if(PORTBbits.RB1){ //check if trigger is still pulled in
        cylinder_set(true);
        bolt_release_led(true);
        IO_RA3_SetInterruptHandler(interrupt_routine_LS2_shooting_A);
    }
    else{
        IO_RA3_SetInterruptHandler(NULL);
        INT1_SetInterruptHandler(NULL);
    }
}

void interrupt_routine_LS2_shooting(void){
    cylinder_set(false);
    bolt_release_led(false);
    IO_RA3_SetInterruptHandler(NULL);
}

void interrupt_routine_LS2_shooting_A(void){
    cylinder_set(false);
    bolt_release_led(false);
    IO_RA3_SetInterruptHandler(NULL);
    INT1_SetInterruptHandler(interrupt_routine_trigger_A);
}


int8_t safety_get(){
    return safetyStatus;
}


void safety_initialize(){
    if(PORTAbits.RA5 && !PORTAbits.RA6 && !PORTAbits.RA4){ safety_set_A();}
    else if(!PORTAbits.RA5 && PORTAbits.RA6 && !PORTAbits.RA4){ safety_set_1();}
    else if(!PORTAbits.RA5 && !PORTAbits.RA6 && PORTAbits.RA4){safety_set_safe();}
    else {safetyStatus = MODE_ERROR; printf("Error while initiating safety \n");}
}

    
void safety_set_safe(){
    safetyStatus = MODE_S;
    INT0_SetInterruptHandler(NULL); //trigger doesn't react
    INT1_SetInterruptHandler(NULL);
    IO_RA3_SetInterruptHandler(NULL);
    
    printf("Safety Mode Changed: S");
}

void safety_set_1(){
    safetyStatus = MODE_1;
    INT0_SetInterruptHandler(interrupt_routine_trigger_1);//trigger reacts by firing single shot
    printf("Safety Mode Changed: 1");
}

void safety_set_A(){
    safetyStatus = MODE_A;
    INT0_SetInterruptHandler(interrupt_routine_trigger_A);
    printf("Safety Mode Changed: A");
}

void safety_check(){
    //put this function in the while loop of main to check the functionality of the safety switch
    switch (safetyStatus) {
            case MODE_S: {
                bolt_release_led(true);
                error_lights(false);
            break;
            }
            case MODE_1: {
                bolt_release_led(false);
                error_lights(true);
            break;
            }
            case MODE_A: {
                bolt_release_led(true);
                error_lights(true);
            break;
            }
            default: {
                bolt_release_led(false);
                error_lights(false);
            break;
            }}}