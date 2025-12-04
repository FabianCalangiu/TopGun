#include <Setup.h>

const int PIR = 2;
const int LED = 7;
const int BTN = 6;
const int SERVO = 5;
const int TRIG = 13;
const int ECHO = 12;
const int TIMER_PERIOD = 100;

// Parameters needed for the servo 
int pos;   
int delta;

bool printedStandby = false;
bool buttonPressed = false;

const int triggerDistance = 100;
const int outOfRangeDist = 350;

Timer* timer;
ServoMotor* pMotor;
DistanceSensor distanceSensor(TRIG, ECHO);

States currentState;

void Setup(){
  Serial.begin(115200);
  pinMode(BTN, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(PIR, INPUT);
  attachInterrupt(digitalPinToInterrupt(PIR), wakeUp, RISING);
  pMotor = new ServoMotorImpl(SERVO);
  pos = 0;
  delta = 1;
  currentState = STANDBY;
  timer = new Timer();
  timer->setupPeriod(TIMER_PERIOD);
}