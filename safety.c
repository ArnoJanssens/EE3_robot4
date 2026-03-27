#include "safety.h"
#include "config.h"
#include "mcc_generated_files/system/interrupt.h"
#include "mcc_generated_files/system/system.h"

volatile int8_t safetyStatus = MODE_ERROR;

void interrupt_routine_trigger_1(void){
    cylinder_set(true);
    laser_set(true);
    TMR1_OverflowCallbackRegister(interrupt_routine_laser);
    TMR1_Start();
    TMR3_OverflowCallbackRegister(interrupt_routine_TMR3_shooting);
    TMR3_Start();
    INT1_SetInterruptHandler(interrupt_routine_LS2_shooting);
}

void interrupt_routine_LS2_shooting(void){
    cylinder_set(false);
    INT1_SetInterruptHandler(NULL);
}

void interrupt_routine_laser(void){
    laser_set(false);
    TMR1_Stop();
}

void interrupt_routine_TMR3_shooting(void){
    cylinder_set(false);
    TMR3_Stop();
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
    printf("Safety Mode Changed: S");
}

void safety_set_1(){
    safetyStatus = MODE_1;
    INT0_SetInterruptHandler(interrupt_routine_trigger_1);//trigger reacts by firing single shot
    printf("Safety Mode Changed: 1");
}

void safety_set_A(){
    safetyStatus = MODE_A;
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