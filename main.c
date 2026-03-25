
#include "mcc_generated_files/system/system.h"
#include <stdint.h>
#include <stdbool.h>
#include "config.h"
#include "startupsequence.h"
#include "safety.h"


/*
    Main application
*/


int main(void)
{
    SYSTEM_Initialize();
    resetActuators();
    INTERRUPT_GlobalInterruptHighEnable();
    INTERRUPT_GlobalInterruptLowEnable();
    safety_initialize();
    startup_sequence_Init();

    while(1)
    {
        
    }
}
    
    

       
        
        
        
      
