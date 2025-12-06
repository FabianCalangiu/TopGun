#include <Arduino.h>
#include <Setup.h>
#include <StateUtils.h>

void setup() {
  Setup();
}

void loop() {
  switch(currentState){
    case STANDBY:
      Standby();
      break;
    case TRACKING:
      Tracking();
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
