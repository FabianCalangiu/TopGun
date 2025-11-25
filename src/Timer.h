#ifndef __TIMER__
#define __TIMER__

class Timer {
    
public:  
  Timer();
  void setupFreq(int freq);  
  /* period in ms */
  void setupPeriod(int period);  
  void waitForNextTick();

};

extern volatile bool timerFlag;


#endif
