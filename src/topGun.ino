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
      LockIn();
      break;
  }
}
