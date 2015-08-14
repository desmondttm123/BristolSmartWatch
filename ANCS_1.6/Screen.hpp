#ifndef SCREEN_H
#define SCREEN_H 

#include <DS3231.h>
#include "U8glib.h"
class Screen
{
private:
  U8GLIB_SH1106_128X64 *u8g;
public:
       Screen(U8GLIB_SH1106_128X64* u8g){this->u8g = u8g;};
  void DrawDate(String date);
  void DrawTime(String time);
  void DrawTemperature(int temperate);
};
#endif
