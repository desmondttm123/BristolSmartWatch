#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>
#include "Clock.hpp"
#include "BluetoothCommunication.hpp"
#include "Screen.hpp"

const int ANCS8SIZE = 8 + 8;
const int INDEX_EVENT = 8;
const int INDEX_CATEGORY = 9;
const int arduinoLED = 17;

char Title [15];
char Message[15];
boolean printed = true;
boolean UID = false;
boolean SMS = false;
boolean EMAIL = false;
boolean MISSEDCALL = false;
boolean INCOMINGCALL = false;
boolean Display = true;
int screen = 0;
int screensleep = 0;
int buttonstate = 8;
int sleepwake = 6;
int tiltscreen = 5;
int vibrate = 4;
int led = 9;

String buffer = "";
String Name = "";
String Subject = "";
String FirstLine = "";
String parsedSubject = "";
String Subject2 = "";
String SecondLine = "";
String parsedSubject2 = "";
String temp ="";
String Line1 = "";
String Line2 = "";
char Index = '0';
char Number = '0';
int ParseEnding;

// Decleration for RTC
DS3231 timer;
Clock clock;

// Declare screen Driver 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Screen displayScreen(&u8g);
// Bluetooth Driver
SoftwareSerial mySerial(10, 16); // RX, TX
BluetoothCommunication bluetoothCommunications(&mySerial); 
void DrawScreen(void) {
  u8g.firstPage();
  do {
    displayScreen.DrawNotifications(Number);
    displayScreen.DrawTime(clock.GetTime());
    displayScreen.DrawDate(clock.GetDate());
    displayScreen.DrawTemperature(clock.GetTemperature());
  }
  while ( u8g.nextPage() );
}

void setup()
{
  //Clock.setHour(21);
  Wire.begin();
  Serial.begin(9600);
  pinMode(arduinoLED, OUTPUT);
  digitalWrite(arduinoLED, LOW);

  //Button number 1 ************************************************************************************
  pinMode(buttonstate, INPUT_PULLUP);           // set pin to input
  digitalWrite(buttonstate, HIGH);


  //Button number 2 ************************************************************************************
  pinMode(sleepwake, INPUT_PULLUP);           // set pin to input
  digitalWrite(sleepwake, HIGH);

  //tilt screen ************************************************************************************
  pinMode(tiltscreen, INPUT_PULLUP);           // set pin to input
  digitalWrite(tiltscreen, LOW);

  // FlashLight  ************************************************************************************
  pinMode(led, OUTPUT);
  digitalWrite(led , LOW);

  //Vibration Motor should be connected to GND  ************************************************************************************
  pinMode(vibrate, OUTPUT);
  digitalWrite(vibrate, LOW);
  mySerial.begin(9600);

}

void checkButtons() {
  if (digitalRead(buttonstate) == LOW) {
    delay(100);
    if (screen == 0) {
      screen = 1;
    }
    else {
      screen = 0;
    }
  }

  if (digitalRead(sleepwake) == LOW) {
    delay(100);
    if (screensleep == 0) {
      screensleep = 1;
    }
    else {
      screensleep = 0;
    }
  }

  // Turn on the Flash LiGHT 
  if (screen == 1) {
    digitalWrite(led , HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

void BluetoothCommunications() {
  while (mySerial.available()) {
    char c = (char)mySerial.read();

    if ((int)c != 0) {
      buffer += c;
    }

    Serial.println(buffer); // try and increase the amount of messega that can fit in this section
    if (buffer.indexOf("OK+ANCS:") == 15) {  
      temp =  buffer.substring(26); // temp contains all the unclean data that needs to be edited
      int ending = temp.indexOf("OK+ANC");
      String data = temp.substring(1, ending); // contains the first part is name followed by message
      String data2 = temp.substring(ending+10);// contains second part of message with ANCS, needs to be filtered again

      if (!mySerial.available()) {
        if (UID == false) {
          Name = data;
        } else if (UID ==true){
          Subject2 = data+data2;
          Serial.println(Subject2);
        }

        int length = parsedSubject2.length();
        if (length >= 1) {
          Subject2 = parsedSubject2.substring(0, length);
        }

        Line1 = Subject2.substring(0, 15);
        Line2 = Subject2.substring(15);

        displayScreen.DrawMessageSender(Name, Subject2);
        buffer = "";
        if(printed == true) {
          mySerial.write(Message);
          printed = false;
          UID = true;
          Display = false;
        } else {
          printed = true;
          UID = false;
          delay(2000); // delay for when the message appears
          Display = true;
        }

        if (Display == false) {
          digitalWrite(vibrate, HIGH);
          delay(300);
          digitalWrite(vibrate, LOW);
        } else {
          digitalWrite(vibrate, LOW);
        }
      }
    }

    if (ANCS8SIZE > buffer.length()) {
      return;
    }

    int indexANCS8 = buffer.indexOf("OK+ANCS8");
    boolean complete = (indexANCS8 + ANCS8SIZE) <= buffer.length();

    if(indexANCS8 != -1 && complete) {
      String string = buffer.substring(indexANCS8, indexANCS8 + ANCS8SIZE);

      buffer = buffer.substring(indexANCS8 + ANCS8SIZE);

      Number = string.charAt(11);
      Index = string.charAt(INDEX_CATEGORY);

      switch (string.charAt(INDEX_CATEGORY)) {
        case '1':
          INCOMINGCALL = true;
          break;
        case '2':
          MISSEDCALL = true;
          break;
        case '4':
          SMS = true;
          break;
        case '6':
          EMAIL = true;
          break;
      }

      strncpy(Title, "AT+ANCS", 7);
      strncpy(&Title[7], &string.c_str()[12],4);
      strncpy(&Title[11], "122", 3);

      strncpy(Message, "AT+ANCS", 7);
      strncpy(&Message[7], &string.c_str()[12],4);
      strncpy(&Message[11], "392", 3);

      mySerial.write(Title);
    }
  }
}

void loop() 
{
  checkButtons();  
  DrawScreen();
  BluetoothCommunications(); 
}

