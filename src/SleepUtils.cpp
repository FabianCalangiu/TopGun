#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <SleepUtils.h>
#include <Setup.h>

void wakeUp(){
  Serial.println("Detecting movement -> Tracking...");
  currentState = TRACKING;
}

void Sleep(){
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
      sleep_enable();
      sleep_mode();  
      sleep_disable();
}