#include "Arduino.h"
#include "Timer.h"
#include "servo_motor_impl.h"
#include "servo_motor.h"

#define PIR 10
#define TRIG 13
#define ECHO 12
#define LED 7
#define BTN 6
#define SERVO 5

int pos;   
int delta;
ServoMotor* pMotor;

void setup() {
  Serial.begin(115200);
  pinMode(BTN, INPUT);
  pinMode(LED, OUTPUT);

  pMotor = new ServoMotorImpl(SERVO);
  pos = 0;
  delta = 1;
}

void loop() {
  
}
