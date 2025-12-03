#include <UDS.h>
#include <Arduino.h>

DistanceSensor::DistanceSensor(int trigger, int eLocator): 
    trig(trigger),
    echo(eLocator), 
    vs(331.45 + 0.62 * 20)
{
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}


float DistanceSensor::getDistance() {
    digitalWrite(trig, LOW);
    delayMicroseconds(10);

    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long tUS = pulseInLong(echo, HIGH);

    double t = tUS / 1e6 / 2.0;
    double d = t * vs;
    return d;
}
