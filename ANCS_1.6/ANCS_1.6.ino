#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>
#include "Clock.hpp"

const int ANCS8SIZE = 8 + 8;
const int INDEX_EVENT = 8;
const int INDEX_CATEGORY = 9;
char Title [15];
char Message[15];
char Time[15];
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
int arduinoLED = 17;

int i = 20;

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

bool Century = false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
byte year, month, date, DoW, hour, minute, second;

// Declare screen Driver 
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);
SoftwareSerial mySerial(10, 16); // RX, TX

void time(void) {
    int temperature;
    temperature = timer.getTemperature();

    u8g.setFont(u8g_font_10x20);
    u8g.setPrintPos(18, 40);
    u8g.print(clock.GetTime());
    Serial.println(clock.GetDate());
    //Date**************************************************************************************
    u8g.setFont(u8g_font_5x7);

    u8g.setPrintPos(25, 50);
    u8g.print(clock.GetDate());

    u8g.setPrintPos(95, 10);
    u8g.print(clock.GetTemperature());
    u8g.setPrintPos(105, 6);
    u8g.print(".");
    u8g.setPrintPos(110, 10);
    u8g.print("C");

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

String buffer = "";
void loop() 
{
 
    //*********************************************************************************************************************
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
    // Turn on the Flash LiGHT  ************************************************************************************
    if (screen == 1) {
        digitalWrite(led , HIGH);
    } else {
        digitalWrite(led, LOW);
    }

    //if (digitalRead(tiltscreen) == LOW ) {
    u8g.firstPage();
    do {
        if (Number != '0') {
            u8g.setFont(u8g_font_5x7);
            u8g.setPrintPos(0, 10);
            u8g.print(Number);
            u8g.setPrintPos(10, 10);
            if (Number == '1') {
                u8g.print("New Notification");
            }
            else {
                u8g.print("New Notifications");
            }
        }
        time();
    }
    while ( u8g.nextPage() );
    //  }else{
    //    
    //       u8g.firstPage();
    //    do {
    //         u8g.print("h");
    //      }
    //   while ( u8g.nextPage() ); 
    //  }

    // To View The Current Message 
    //  if (screen == 1 && screensleep == 0) {
    //       
    //    u8g.firstPage();
    //   do {
    //
    //      u8g.setFont(u8g_font_5x7);
    //
    //      u8g.setPrintPos(0, 10);
    //      u8g.print("From : ");
    //      u8g.setPrintPos(35, 10);
    //      u8g.print(Name);
    //      u8g.setPrintPos(0, 25);
    //      u8g.print(Line1);
    //     
    //      u8g.setPrintPos(0, 35);
    //      u8g.print(Line2);
    //
    //    }
    //    while ( u8g.nextPage() );
    //  }

    //*********************************************************************************************************************

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
            // Serial.println(data2);

            //When there is no data left to be read from serial port
            //print data to the screen
            if (!mySerial.available()) {
                if (UID == false) {
                    Name = data;
                }else if (UID ==true){
                    Subject2 = data+data2;
                    //Serial.println(Subject2);
                }

                int length = parsedSubject2.length();
                if (length >= 1) {
                    Subject2 = parsedSubject2.substring(0, length);
                }

                Line1 = Subject2.substring(0, 15);
                Line2 = Subject2.substring(15);

                u8g.firstPage();
                do {

                    u8g.setFont(u8g_font_5x7);
                    u8g.setPrintPos(0, 10);
                    u8g.print("From : ");

                    u8g.setPrintPos(30, 10);
                    u8g.print(Name);
                    //****************************************************************************************************************
                    u8g.setPrintPos(0, 20);
                    u8g.print(Subject2);
                    //***************************************************************************************************************
                }
                while ( u8g.nextPage() );
                buffer = "";
                delay(200);
                if (printed == true) {
                    //mySerial.write(Message);
                    buffer = "";
                    printed = false;
                    UID = true;
                    Display = false;
                }

                else {
                    printed = true;
                    UID = false;
                    buffer = "";
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
        if (-1 == indexANCS8) continue;
        boolean complete = (indexANCS8 + ANCS8SIZE) <= buffer.length();
        if (!complete) continue;

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
        strcpy(Title, "AT+ANCS");
        Title[7] = string.charAt(12);
        Title[8] = string.charAt(13);
        Title[9] = string.charAt(14);
        Title[10] = string.charAt(15);
        Title[11] = '1';
        Title[12] = '2';
        Title[13] = '2';
        
        strcpy(Message, "AT+ANCS");
        Message[9] = string.charAt(14);
        Message[10] = string.charAt(15);
        Message[11] = '3';
        Message[12] = '9';
        Message[13] = '2';

        //mySerial.write(Title);
       

    }
}
