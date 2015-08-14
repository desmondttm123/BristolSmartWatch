#ifndef SCREEN_H
#define SCREEN_H 

#include <DS3231.h>

class Screen
{
private:

public:
  void DrawDate(String date){};
  void DrawTime(String time){};
  void DrawTemperature(){};
};
#endif
