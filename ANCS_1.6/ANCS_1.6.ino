#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>
#include "Clock.h"
#include "BluetoothCommunication.h"
#include "Screen.h"

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
Clock clock; 

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); 

Screen displayScreen(&u8g);

SoftwareSerial mySerial(10, 16); // RX, TX

BluetoothCommunication bluetoothCommunication(&mySerial); 

/*
 * FUNCTION DrawScreen()
 * 
 * Calls all of the appropriate methods to draw all information 
 * to the screen
 * 
 * @param (void)
 * @return (void)
 * 
 */ 
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

/*
 * FUNCTION setup()
 * 
 * Configures all of the states of the hardware
 * 
 * @param (void)
 * @return (void)
 * 
 */ 
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

/*
 * FUNCTION CheckButtons()
 * 
 * Checks the states of all the hardware buttons.
 * 
 * @param (void)
 * @return (void)
 * 
 */ 
void checkButtons() {
  //Goes to notification page
  if (digitalRead(buttonstate) == LOW) {
    delay(100);
    if (screen == 0) {
      screen = 1;
    }
    else {
      screen = 0;
    }
  }

  // Turns the screen off
  if (digitalRead(sleepwake) == LOW) {
    delay(100);
    if (screensleep == 0) {
      screensleep = 1;
    }
    else {
      screensleep = 0;
    }
  }

  // Turns on the Flash Light
  if (screen == 1) {
    digitalWrite(led , HIGH);
  } else {
    digitalWrite(led, LOW);
  }
}

/*
 * FUNCTION BluetoothCommuncations()
 * 
 * Calls BluetoothCommuncation.Read() to read any information
 * over Bluetooth. Writes a notification to the screen if 
 * there is a new notifcation and also vibrates.
 * 
 * @param (void)
 * @return (void)
 * 
 */ 
void BluetoothCommunications() {
  bluetoothCommunication.Read();
  
  if(bluetoothCommunication.GetNewMessage()) {
    displayScreen.DrawMessageSender(bluetoothCommunication.GetName(), 
                                    bluetoothCommunication.GetSubject());
    bluetoothCommunication.SetNewMessage(false);
   
    //Time to display message
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

/*
 * FUNCTION Loop()
 * 
 * Makes appropriate function calls each time it is called
 * by the arduino 
 * 
 * @param (void)
 * @return (void)
 * 
 */ 
void loop() 
{
  checkButtons();  
  DrawScreen();
  BluetoothCommunications(); 
}

