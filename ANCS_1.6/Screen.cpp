#include "Screen.h"
#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>

//TODO Configure the font_sizes and
//x,y positions as constants in header file
void Screen::DrawTime(String time) {
    u8g->setFont(u8g_font_10x20);
    u8g->setPrintPos(18, 40);
    u8g->print(time);
}

void Screen::DrawDate(String date) {
    u8g->setFont(u8g_font_5x7);
    u8g->setPrintPos(25, 50);
    u8g->print(date);
}

void Screen::DrawTemperature(int temperature) {
    u8g->setPrintPos(95, 10);
    u8g->print(temperature);
    u8g->setPrintPos(105, 6);
    u8g->print(".");
    u8g->setPrintPos(110, 10);
    u8g->print("C");
}
void Screen::DrawNotifications(char numOfNotifications) {
  if (numOfNotifications != '0') {
    u8g->setFont(u8g_font_5x7);
    u8g->setPrintPos(0, 10);
    u8g->print(numOfNotifications);
    u8g->setPrintPos(10, 10);
    if (numOfNotifications == '1') {
      u8g->print("New Notification");
    }
    else {
      u8g->print("New Notifications");
    }
  }
}
void Screen::DrawMessageSender(String sender, String subject) {
  u8g->firstPage();
  do {
    //Print Message Sender
    u8g->setFont(u8g_font_5x7);
    u8g->setPrintPos(0, 10);
    u8g->print("From : ");
    u8g->setPrintPos(30, 10);
    u8g->print(sender);
    //Print Message Subject
    u8g->setPrintPos(0, 20);
    u8g->print(subject);
    //***************************************************************************************************************
  }
  while ( u8g->nextPage() );
  delay(200);
}


