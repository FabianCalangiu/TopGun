#include <Arduino.h>
#include <Timer.h>
#include <Setup.h>
#include <UDS.h>
#include <SleepUtils.h>

void setup() {
  Setup();
}

void loop() {
  switch(currentState){
    case STANDBY:
      if(!printedStandby) {
        Serial.println("Powering down...");
        printedStandby = true;
      }
      Sleep();
      break;
    case TRACKING:
      Serial.print("Target going at ");
      Serial.print(distanceSensor.getVelocity());
      Serial.println(" m/s.");
      
      if((distanceSensor.getDistance()) < triggerDistance) {
        Serial.println("Target in range, go to LOCKIN! ");
        currentState = LOCKIN;
      }

      if((distanceSensor.getDistance()) > outOfRangeDist) {
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
      int randInt = (int) random(0, 10);

      if((distanceSensor.getDistance()) > triggerDistance){
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
          pos = 0;
          pMotor->setPosition(pos);
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
