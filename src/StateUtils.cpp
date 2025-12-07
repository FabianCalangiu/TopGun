#include <StateUtils.h>

void Standby(){
    if(!printedStandby) {
        Serial.println("Powering down...");        
        printedStandby = true;
    }
    
    // Check SleepUtils.h and .cpp to see what this function does
    Sleep();
}

void Tracking(){
    // Calculates and prints velocity (See UDS.h and .cpp files)
    Serial.print("Target going at ");
    Serial.print(distanceSensor.getVelocity());
    Serial.println(" m/s.");
    
    // Targeting range and state guards
    if((distanceSensor.getDistance()) < triggerDistance) {
      Serial.println("Target in range, Locking In! ");
      currentState = LOCKIN;
    }
    if((distanceSensor.getDistance()) > outOfRangeDist) {
      Serial.println("Target out of range, going STANDBY! ");
      currentState = STANDBY;
    }
}

void LockIn(){
    digitalWrite(LED, HIGH);
    pMotor->on();
    pos = (int)random(0,180);
    buttonPressed = digitalRead(BTN);
    delay(125);
    pMotor->setPosition(pos);
    int randInt = (int) random(0, 10);

    // Checks if target escaped (over 100cm threshold)
    if((distanceSensor.getDistance()) > triggerDistance){
        Serial.println("Target escaped... tracking.");
        buttonPressed = false;
        printedStandby = false;
        digitalWrite(LED, LOW);
        pMotor->off();
        currentState = TRACKING;
    }
    
    // Parses if user shot at the target
    if(buttonPressed){
        // Probability of 50% to miss
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
}