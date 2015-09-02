#ifndef ClOCK_H
#define CLOCK_H 

#include <DS3231.h>

/*
 *  CLASS Clock
 *  
 *  Class wraps the DS3231 object and had
 *  methods to get information from it
 */
 
class Clock
{
private:
  DS3231 timer; 
  bool PM, Century=false, h12;
  
public:
    Clock(){};

 /*
  * FUNCTION GetTime()
  * 
  * Returns a human readable String containing the current time.
  * 
  * @param (void)
  * @return String : Time
  * 
  */ 
  String GetTime();

 /*
  * FUNCTION GetDate()
  * 
  * Returns a human readable String containing the date.
  * 
  * @param (void)
  * @return String : The date
  * 
  */ 
  String GetDate();

 /*
  * FUNCTION GetTemperature()
  * 
  * Returns the temperature as in integer in degrees C.
  * 
  * @param (void)
  * @return int : timer.getTemperature
  * 
  */ 
  int GetTemperature();
};
#endif
