/* 
 * File:   config.h
 * Author: janss
 *
 * Created on March 10, 2026, 1:06 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#define N_ACTUATORS 10
#include <stdbool.h>

void resetActuators(void);
void reset();
void error_lights(bool on);
void cylinder_set(bool extended);
void blocking_solenoid_set(bool enable);
void bolt_release_led(bool on);
void laser_set(bool on);


#endif	/* CONFIG_H */

