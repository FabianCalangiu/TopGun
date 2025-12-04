#include <Setup.h>

// Initialize sensor parameters
DistanceSensor::DistanceSensor(int trigger, int eLocator): 
    trig(trigger),
    echo(eLocator), 
    vs(331.45 + 0.62 * 20)

// Constructor body
{
    pinMode(trig, OUTPUT); 
    pinMode(echo, INPUT);
}

// Function to calculate the distance
float DistanceSensor::getDistance() {
    digitalWrite(trig, LOW);
    delayMicroseconds(10);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long tUS = pulseInLong(echo, HIGH);

    double t = tUS / 1e6 / 2.0;
    double d = t * vs;
    return d * 100;
}

float DistanceSensor::getVelocity(){
    float vel;
    float d1 = getDistance();
    timer->waitForNextTick();
    float d2 = getDistance();
    float distDiff = d1 - d2;
    if(distDiff < 0){
        distDiff = -distDiff;
    }
    vel = (distDiff / 100) / 0.1;

    return vel;
}
