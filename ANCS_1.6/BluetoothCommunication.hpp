#ifndef BLUETOOTHCOMMUNICATION_H
#define BLUETOOTHCOMMUNICATION_H 

#include <DS3231.h>
#include "Screen.hpp"
#include <SoftwareSerial.h>

class BluetoothCommunication 
{
  SoftwareSerial *mySerial;
  char Title [15];
  char Message[15];
  boolean printed = true;
  boolean UID = false;
  boolean SMS = false;
  boolean EMAIL = false;
  boolean MISSEDCALL = false;
  boolean INCOMINGCALL = false;
  boolean Display = true;
  String buffer = "";
  String temp = "";
  String Name = "";
  String Subject2 = "";
  String parsedSubject2 = ""; 
  String Line1 = "";
  String Line2 = "";
  const int ANCS8SIZE = 8 + 8;
  const int INDEX_CATEGORY = 9;
  int Number;
  char Index = '0';
public:
    BluetoothCommunication(SoftwareSerial *mySerial){
      this->mySerial = mySerial;
    };
    String Read();
    String GetTitle(){return Title};
    String GetSubject(){return Subject2);
};
#endif
