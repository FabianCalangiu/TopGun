#include <Arduino.h>
#include <Timer.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <Setup.h>
#include <UDS.h>

Timer* timer;

void setup() {
  Setup();
  timer = new Timer();
}

void wakeUp(){
  Serial.println("Detecting movement -> Tracking...");
  currentState = TRACKING;
}

void loop() {
  switch(currentState){
    case STANDBY:
      if(!printedStandby) {
        Serial.println("Powering down...");
        printedStandby = true;
      }
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
      sleep_enable();
      sleep_mode();  
      sleep_disable();
      break;
    case TRACKING:
      delay(100);
      if((distanceSensor.getDistance() * 100) < triggerDistance) {
        Serial.println("Target in range, go to LOCKIN! ");
        currentState = LOCKIN;
      }

      if((distanceSensor.getDistance() * 100) > outOfRangeDist) {
        Serial.println("Target out of range, go to STANDBY! ");
        currentState = STANDBY;
      }
      break;
    case LOCKIN:

      digitalWrite(LED, HIGH);
      pMotor->on();
      pos = (int)random(0,180);
      buttonPressed = digitalRead(BTN);
      delay(125);
      pMotor->setPosition(pos);
      pos -= delta;
      delta = -delta;
      int randInt = (int) random(0, 10);

      if((distanceSensor.getDistance() * 100) > triggerDistance){
          Serial.println("Target escaped... tracking.");
          buttonPressed = false;
          printedStandby = false;
          digitalWrite(LED, LOW);
          pMotor->off();
          currentState = TRACKING;
      }
      
      if(buttonPressed){
        if(randInt % 2 == 0) {
          Serial.println("Target hit!");
          buttonPressed = false;
          printedStandby = false;
          digitalWrite(LED, LOW);
          pMotor->off();
          delay(1000);
          currentState = STANDBY;
        } else {
          Serial.println("Target missed! Retry!");
          buttonPressed = false;
        }
      }
      break;
  }
  
}
