 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
*/

/*
© [2026] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include <stdint.h>
#include <stdbool.h>

#define N_ACTUATORS 11

static volatile uint16_t offCountdownMs = 0;
static volatile uint8_t currentAct = 0;
static volatile bool testDone = false;
/*
    Main application
*/

static inline void actuator_on(uint8_t i){
    switch(i){
        //turn on all big solenoids 
        case 0: IO_RD0_SetHigh(); break; //block sol
        case 1: IO_RD2_SetHigh(); break; //valve
    
    //turn on all small solenoids
        case 2: IO_RA1_SetHigh(); break; // mag release
        case 3: IO_RC0_SetHigh(); break; // switch led
        case 4: IO_RB5_SetHigh(); break; //laser
    
    //connection to outer pcb
    
        case 5: IO_RD3_SetHigh(); break; //uOutChaser
        case 6: IO_RD5_SetHigh(); break; //uCoutoutofammo CHANGE TO RD5
        case 7: IO_RD4_SetHigh(); break; //uCoutBoltHold
        case 8: IO_RD1_SetHigh(); break; //UCoutFout
        case 9: IO_RA4_SetHigh(); break; //uCoutLEDBOLTR
        case 10: IO_RB3_SetHigh(); break; //uCoutLEDMAGR
    }
}

static inline void actuator_off(uint8_t i){
    switch(i){
        //turn on all big solenoids 
        case 0: IO_RD0_SetLow(); break;//block sol
        case 1: IO_RD2_SetLow(); break; //valve
    
    //turn on all small solenoids
        case 2: IO_RA1_SetLow(); break; // mag release
        case 3: IO_RC0_SetLow(); break; // switch led
        case 4: IO_RB5_SetLow(); break; //laser
    
    //connection to outer pcb
    
        case 5: IO_RD3_SetLow(); break; //uOutChaser
        case 6: IO_RD5_SetLow(); break; //uCoutoutofammo CHANGE TO RD5
        case 7: IO_RD4_SetLow(); break; //uCoutBoltHold
        case 8: IO_RD1_SetLow(); break; //UCoutFout
        case 9: IO_RA4_SetLow(); break; //uCoutLEDBOLTR
        case 10: IO_RB3_SetLow(); break; //uCoutLEDMAGR
    }
}

static void ActuatorTestTick_1ms(void)  //chatgpt code
{
    // If we're currently timing an ON pulse
    if (offCountdownMs > 0)
    {
        offCountdownMs--;
        if (offCountdownMs == 0)
        {
            actuator_off(currentAct);
            currentAct++;
            if (currentAct >= N_ACTUATORS){
                testDone = true;
                return;
            }
        }
        return;
    }

    // Idle -> start next actuator pulse (1 second)
    actuator_on(currentAct);
    offCountdownMs = 1000; // 1000ms = 1s
}

static void resetActuators(void){
    IO_RD0_SetLow(); //block sol
    IO_RD2_SetLow(); //valve
    IO_RA1_SetLow(); // mag release
    IO_RC0_SetLow(); // switch led
    IO_RB5_SetLow(); //laser    
    IO_RD3_SetLow(); //uOutChaser
    IO_RD5_SetLow(); //uCoutoutofammo CHANGE TO RD5
    IO_RD4_SetLow(); //uCoutBoltHold
    IO_RD1_SetLow(); //UCoutFout
    IO_RA4_SetLow(); //uCoutLEDBOLTR
    IO_RB3_SetLow(); //uCoutLEDMAGR
}

int main(void)
{
    SYSTEM_Initialize();
    resetActuators();
    
    TMR0_OverflowCallbackRegister(ActuatorTestTick_1ms); 
    INTERRUPT_GlobalInterruptEnable();
    
    //IO_RD0_SetHigh();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
      
    
    //turn on all big solenoids 
    //IO_RD0_SetHigh(); //block sol
    //IO_RD2_SetHigh(); //valve
    
    //turn on all small solenoids
    //IO_RA1_SetHigh(); // mag release
    
    
    //IO_RD0_SetHigh(); // switch led
    
    //IO_RB5_SetHigh(); //laser
    
    //connection to outer pcb
    
    //IO_RD3_SetHigh(); //uOutChaser
    //IO_RD5_SetHigh(); //uCoutoutofammo CHANGE TO RD5
    //IO_RD4_SetHigh(); //uCoutBoltHold
    //IO_RD1_SetHigh(); //UCoutFout
    //IO_RA4_SetHigh(); //uCoutLEDBOLTR
    //IO_RB3_SetHigh(); //uCoutLEDMAGR
    
    
    
    while(1)
    {
        
    }    
    
}