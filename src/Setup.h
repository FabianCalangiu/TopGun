#ifndef __SETUP__
#define __SETUP__
#include <servo_motor_impl.h>
#include <servo_motor.h>
#include <UDS.h>

void Setup();
void wakeUp();

extern ServoMotor* pMotor;
extern DistanceSensor distanceSensor;

enum States{
  STANDBY,
  TRACKING,
  LOCKIN
};
extern States currentState;

extern const int PIR;
extern const int LED;
extern const int BTN;
extern const int TIMER_PERIOD;

extern int pos;   
extern int delta;
extern bool printedStandby; 
extern bool buttonPressed; 
extern const int triggerDistance; 
extern const int outOfRangeDist; 

#endif