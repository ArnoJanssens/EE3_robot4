/* 
 * File:   safety.h
 * Author: janss
 *
 * Created on March 17, 2026, 8:34 PM
 */

#ifndef SAFETY_H
#define	SAFETY_H
#include <stdint.h>

#define MODE_S 0
#define MODE_1 1
#define MODE_A 2
#define MODE_ERROR 3

volatile int8_t safetyStatus;

void safety_check();
void safety_initialize();
void safety_set_safe();
void safety_set_1();
void safety_set_A();
void interrupt_routine_trigger_1(void);
void interrupt_routine_LS2_shooting(void);
        

#endif	/* SAFETY_H */

