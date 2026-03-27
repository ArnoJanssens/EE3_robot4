/**
  * TMR3 Generated Timer Driver File
  *
  * @file tmr3.c
  *
  * @ingroup timerdriver
  *
  * @brief Driver implementation for the TMR3 Timer driver
  *
  * @version TMR3 Timer Driver Version 4.0.0
  * 
  * @version Package Version 5.1.0
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

/**
 * Section: Included Files
*/

#include <xc.h>
#include "../tmr3.h"

const struct TIMER_INTERFACE Timer3 = {
    .Initialize = TMR3_Initialize,
    .Deinitialize = TMR3_Deinitialize,
    .Start = TMR3_Start,
    .Stop = TMR3_Stop,
    .PeriodSet = TMR3_PeriodSet,
    .PeriodGet = TMR3_PeriodGet,
    .CounterGet = TMR3_CounterGet,
    .CounterSet = TMR3_CounterSet,
    .MaxCountGet = TMR3_MaxCountGet,
    .TimeoutCallbackRegister = TMR3_OverflowCallbackRegister,
    .Tasks = NULL
};

static volatile uint16_t timer3ReloadVal;
static void TMR3_DefaultOverflowCallback(void);
static void (*TMR3_OverflowCallback)(void);

void TMR3_Initialize(void)
{
    T3CONbits.TMR3ON = 0;             // TMRON disabled

    T3GCON = (0 << _T3GCON_T3GGO_POSN)   // T3GGO done
        | (0 << _T3GCON_T3GSPM_POSN)   // T3GSPM disabled
        | (0 << _T3GCON_T3GTM_POSN)   // T3GTM disabled
        | (0 << _T3GCON_T3GPOL_POSN)   // T3GPOL low
        | (0 << _T3GCON_T3GE_POSN);  // T3GE disabled

    T3GATE = (0 << _T3GATE_GSS_POSN);  // GSS T3G_pin

    T3CLK = (4 << _T3CLK_CS_POSN);  // CS LFINTOSC

    TMR3H = 0xFE;              // Period 100.3871ms; Timer clock 3875 Hz
    TMR3L = 0x7B;

    timer3ReloadVal=((uint16_t)TMR3H << 8) | TMR3L;
    TMR3_OverflowCallback = TMR3_DefaultOverflowCallback;

    PIR5bits.TMR3IF = 0;   
    PIE5bits.TMR3IE = 1;
  
    T3CON = (1 << _T3CON_TMR3ON_POSN)   // TMR3ON enabled
        | (0 << _T3CON_T3RD16_POSN)   // T3RD16 disabled
        | (1 << _T3CON_nT3SYNC_POSN)   // nT3SYNC do_not_synchronize
        | (3 << _T3CON_CKPS_POSN);  // CKPS 1:8
}

void TMR3_Deinitialize(void)
{
    T3CONbits.TMR3ON = 0;             // TMRON disabled
    
    T3CON = 0x0;
    T3GCON = 0x0;
    T3GATE = 0x0;
    T3CLK = 0x0;
    TMR3H = 0x0;
    TMR3L = 0x0;

    PIR5bits.TMR3IF = 0;
    PIE5bits.TMR3IE = 0;

    PIR5bits.TMR3GIF = 0;
    PIE5bits.TMR3GIE = 0;
}

void TMR3_Start(void)
{   
    T3CONbits.TMR3ON = 1;
}

void TMR3_Stop(void)
{ 
    T3CONbits.TMR3ON = 0;
}

uint32_t TMR3_CounterGet(void)
{
    uint16_t readVal;
    uint8_t readValHigh;
    uint8_t readValLow;
    	
    readValLow = TMR3L;
    readValHigh = TMR3H;
    
    readVal = ((uint16_t)readValHigh << 8) | readValLow;

    return (uint32_t)readVal;
}

void TMR3_CounterSet(uint32_t timerVal)
{
    if(1U == T3CONbits.nT3SYNC)
    {
        bool onState = T3CONbits.TMR3ON;

        T3CONbits.TMR3ON = 0;      
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;       
        T3CONbits.TMR3ON = onState;
    }
    else
    {      
        TMR3H = (uint8_t)(timerVal >> 8);
        TMR3L = (uint8_t)timerVal;
    }
}

void TMR3_PeriodSet(uint32_t periodVal)
{
    timer3ReloadVal =  TMR3_MAX_COUNT - (uint16_t)periodVal;
    /* cppcheck-suppress misra-c2012-8.7 */
    TMR3_CounterSet(timer3ReloadVal);
}

uint32_t TMR3_PeriodGet(void)
{
    return ((uint32_t)TMR3_MAX_COUNT - timer3ReloadVal);
}

uint32_t TMR3_MaxCountGet(void)
{
    return (uint32_t)TMR3_MAX_COUNT;
}

void __interrupt(irq(TMR3),base(8)) TMR3_OverflowISR()
{
    /* cppcheck-suppress misra-c2012-8.7 */
    TMR3_CounterSet(timer3ReloadVal);

    // The ticker is set to 1 -> The callback function gets called every time this ISR executes.
    if(NULL != TMR3_OverflowCallback)
    {
        TMR3_OverflowCallback();
    }
    PIR5bits.TMR3IF = 0;
}

void TMR3_OverflowCallbackRegister(void (* CallbackHandler)(void))
{
    TMR3_OverflowCallback = CallbackHandler;
}

static void TMR3_DefaultOverflowCallback(void)
{
    // Default interrupt handler
}
/**
  End of File
*/
