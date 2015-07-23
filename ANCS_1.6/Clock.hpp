/*
  Clock.h - Library for flashing Clock code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Clock_h
#define Clock_h

#include "Arduino.h"

class Clock
{
  public:
    Clock(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};

#endif
