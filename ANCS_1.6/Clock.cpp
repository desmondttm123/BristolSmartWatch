/*
  Clock.cpp - Library for flashing Clock code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Clock.hpp"

Clock::Clock(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void Clock::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);  
}

void Clock::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}
