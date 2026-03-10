/* 
 * File:   startupsequence.h
 * Author: janss
 *
 * Created on March 10, 2026, 4:11 PM
 */

#ifndef STARTUPSEQUENCE_H
#define	STARTUPSEQUENCE_H

void startup_sequence_actuator_on(int8_t i);

void startup_sequence_actuator_off(int8_t i);

void startup_sequence_OnTimerInterrupt(void);

void startup_sequence_Init(void);

#endif	/* STARTUPSEQUENCE_H */

