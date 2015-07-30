#ifndef ClOCK_H
#define CLOCK_H 

#include <DS3231.h>

class Clock
{
private:
  DS3231 timer; 
  bool PM, Century=false, h12;

public:
    Clock(){};
    String GetTime();
};
#endif
