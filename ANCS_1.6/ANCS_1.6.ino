#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>
#include "Clock.hpp"
#include "BluetoothCommunication.hpp"
#include "Screen.hpp"

const int arduinoLED = 17;

int screen = 0;
int screensleep = 0;
int buttonstate = 8;
int sleepwake = 6;
int tiltscreen = 5;
int vibrate = 4;
int led = 9;
int Number;
// Decleration for RTC
DS3231 timer;
Clock clock;

// Declare screen Driver 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);
Screen displayScreen(&u8g);
// Bluetooth Driver
SoftwareSerial mySerial(10, 16); // RX, TX
BluetoothCommunication bluetoothCommunication(&mySerial); 
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
  bluetoothCommunication.Read();
  if(bluetoothCommunication.GetNewMessage()) {
    displayScreen.DrawMessageSender(bluetoothCommunication.GetName(), 
                                    bluetoothCommunication.GetSubject());
    bluetoothCommunication.SetNewMessage(false);
    delay(2000);
  }
  int temp = bluetoothCommunication.GetNumber();
  if(temp != Number && temp > '0') {
    digitalWrite(vibrate, HIGH);
    delay(300);
    digitalWrite(vibrate, LOW);
  }
  Number = bluetoothCommunication.GetNumber();
}

void loop() 
{
  checkButtons();  
  DrawScreen();
  BluetoothCommunications(); 
}

