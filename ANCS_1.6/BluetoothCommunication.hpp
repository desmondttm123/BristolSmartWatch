#ifndef BLUETOOTHCOMMUNICATION_H
#define BLUETOOTHCOMMUNICATION_H 

#include <DS3231.h>
#include "Screen.hpp"
#include <SoftwareSerial.h>

class BluetoothCommunication 
{
private:
  Screen *screen; 
  SoftwareSerial *mySerial;
public:
    BluetoothCommunication(Screen *screen, SoftwareSerial *mySerial){
      this->screen = screen;
      this->mySerial = mySerial;
    };
};
#endif
