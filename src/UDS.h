#ifndef __UDS__
#define  __UDS__

class DistanceSensor {
    private:
        int trig;
        int echo;
        const double vs;
    
    public:
        DistanceSensor(int trigger, int eLocator);
        float getDistance();
};

#endif
