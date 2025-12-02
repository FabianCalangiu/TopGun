#include "Arduino.h"
#include "Timer.h"
#include "servo_motor_impl.h"
#include "servo_motor.h"
#include <avr/sleep.h>
#include <avr/interrupt.h>

#define PIR 2
#define TRIG 13
#define ECHO 12
#define LED 7
#define BTN 6
#define SERVO 5

#define TIMER_PERIOD 100

int pos;   
int delta;
ServoMotor* pMotor;

bool printedStandby = false;
bool buttonPressed = false;

const double vs = 331.45 + 0.62*20;

enum States{
  STANDBY,
  TRACKING,
  LOCKIN
};
States currentState;

Timer* timer;

const int triggerDistance = 100;
const int outOfRangeDist = 350;

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIR), wakeUp, RISING);
  pMotor = new ServoMotorImpl(SERVO);
  pos = 0;
  delta = 1;
  currentState = STANDBY;

  timer = new Timer();
}

float getDistance()
{
    digitalWrite(TRIG,LOW);
    delayMicroseconds(10);

    digitalWrite(TRIG,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG,LOW);
    
    long tUS = pulseInLong(ECHO, HIGH);

    double t = tUS / 1000.0 / 1000.0 / 2;
    double d = t*vs;
    return d;
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
      if((getDistance() * 100) < triggerDistance) {
        Serial.println("Target in range, go to LOCKIN! ");
        currentState = LOCKIN;
      }

      if((getDistance() * 100) > outOfRangeDist) {
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



      if((getDistance() * 100) > triggerDistance){
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
