#include <StateUtils.h>

void Standby(){
    if(!printedStandby) {
        Serial.println("Powering down...");        
        printedStandby = true;
    }
    
    Sleep();
}

void Tracking(){
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
}