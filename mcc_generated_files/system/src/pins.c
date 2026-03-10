/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.1.1
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

#include "../pins.h"

void (*IO_RA5_InterruptHandler)(void);
void (*IO_RA6_InterruptHandler)(void);
void (*IO_RA7_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x0;
    LATD = 0x0;
    LATE = 0x0;
    LATF = 0x0;
    /**
    ODx registers
    */
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    ODCOND = 0x0;
    ODCONE = 0x0;
    ODCONF = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0xEF;
    TRISB = 0xD7;
    TRISC = 0xFE;
    TRISD = 0x0;
    TRISE = 0xF;
    TRISF = 0xFF;

    /**
    ANSELx registers
    */
    ANSELA = 0x6;
    ANSELB = 0xD0;
    ANSELC = 0xFE;
    ANSELD = 0x0;
    ANSELE = 0x7;
    ANSELF = 0xFF;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;
    WPUD = 0x0;
    WPUE = 0x0;
    WPUF = 0x0;


    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    SLRCOND = 0xFF;
    SLRCONE = 0x7;
    SLRCONF = 0xFF;

    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLD = 0xFF;
    INLVLE = 0xF;
    INLVLF = 0xFF;

   /**
    RxyI2C | RxyFEAT registers   
    */
    RB1I2C = 0x0;
    RB2I2C = 0x0;
    RC3I2C = 0x0;
    RC4I2C = 0x0;
    /**
    PPS registers
    */
    INT0PPS = 0x9; //RB1->INTERRUPT MANAGER:INT0;
    INT1PPS = 0xA; //RB2->INTERRUPT MANAGER:INT1;

   /**
    IOCx registers 
    */
    IOCAP = 0xE0;
    IOCAN = 0xE0;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x0;
    IOCCN = 0x0;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;

    IO_RA5_SetInterruptHandler(IO_RA5_DefaultInterruptHandler);
    IO_RA6_SetInterruptHandler(IO_RA6_DefaultInterruptHandler);
    IO_RA7_SetInterruptHandler(IO_RA7_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin IO_RA5
    if(IOCAFbits.IOCAF5 == 1)
    {
        IO_RA5_ISR();  
    }
    // interrupt on change for pin IO_RA6
    if(IOCAFbits.IOCAF6 == 1)
    {
        IO_RA6_ISR();  
    }
    // interrupt on change for pin IO_RA7
    if(IOCAFbits.IOCAF7 == 1)
    {
        IO_RA7_ISR();  
    }
}
   
/**
   IO_RA5 Interrupt Service Routine
*/
void IO_RA5_ISR(void) {

    // Add custom IO_RA5 code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_RA5_InterruptHandler)
    {
        IO_RA5_InterruptHandler();
    }
    IOCAFbits.IOCAF5 = 0;
}

/**
  Allows selecting an interrupt handler for IO_RA5 at application runtime
*/
void IO_RA5_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_RA5_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IO_RA5
*/
void IO_RA5_DefaultInterruptHandler(void){
    // add your IO_RA5 interrupt custom code
    // or set custom function using IO_RA5_SetInterruptHandler()
}
   
/**
   IO_RA6 Interrupt Service Routine
*/
void IO_RA6_ISR(void) {

    // Add custom IO_RA6 code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_RA6_InterruptHandler)
    {
        IO_RA6_InterruptHandler();
    }
    IOCAFbits.IOCAF6 = 0;
}

/**
  Allows selecting an interrupt handler for IO_RA6 at application runtime
*/
void IO_RA6_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_RA6_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IO_RA6
*/
void IO_RA6_DefaultInterruptHandler(void){
    // add your IO_RA6 interrupt custom code
    // or set custom function using IO_RA6_SetInterruptHandler()
}
   
/**
   IO_RA7 Interrupt Service Routine
*/
void IO_RA7_ISR(void) {

    // Add custom IO_RA7 code

    // Call the interrupt handler for the callback registered at runtime
    if(IO_RA7_InterruptHandler)
    {
        IO_RA7_InterruptHandler();
    }
    IOCAFbits.IOCAF7 = 0;
}

/**
  Allows selecting an interrupt handler for IO_RA7 at application runtime
*/
void IO_RA7_SetInterruptHandler(void (* InterruptHandler)(void)){
    IO_RA7_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IO_RA7
*/
void IO_RA7_DefaultInterruptHandler(void){
    // add your IO_RA7 interrupt custom code
    // or set custom function using IO_RA7_SetInterruptHandler()
}
/**
 End of File
*/