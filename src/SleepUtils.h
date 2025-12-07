#ifndef __SLEEPUTILS__
#define __SLEEPUTILS__

#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <Setup.h>

// Functions needed to enter/exit sleep mode

void wakeUp();
void Sleep();

#endif

