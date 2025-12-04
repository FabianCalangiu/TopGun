#ifndef __UDS__
#define  __UDS__

// Ultrasonic Distance Sensor 

#include <Setup.h>

class DistanceSensor {
    private:
        int trig;
        int echo;
        const double vs;
    
    public:
        DistanceSensor(int trigger, int eLocator);
        float getDistance();
        float getVelocity();
};

#endif
