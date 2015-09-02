#include "Screen.h"
#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>

/*
 * FUNCTION DrawTime()
 * 
 * Sets the position and font size for the time and
 * draws time to screen.
 * 
 * @param (String time)
 * @return (void)
 * 
 */ 
void Screen::DrawTime(String time) {
    u8g->setFont(u8g_font_10x20);
    u8g->setPrintPos(18, 40);
    u8g->print(time);
}

/*
 * FUNCTION DrawDate()
 * 
 * Sets the position and font size for the Date
 * and draws to screen.
 * 
 * @param (String date)
 * @return (void)
 * 
 */ 
void Screen::DrawDate(String date) {
    u8g->setFont(u8g_font_5x7);
    u8g->setPrintPos(25, 50);
    u8g->print(date);
}

/*
 * FUNCTION DrawTemperature()
 * 
 * Sets the position and font size for the temperature
 * and draws to screen.
 * 
 * @param (String temperature)
 * @return (void)
 * 
 */ 
void Screen::DrawTemperature(int temperature) {
    u8g->setPrintPos(95, 10);
    u8g->print(temperature);
    u8g->setPrintPos(105, 6);
    u8g->print(".");
    u8g->setPrintPos(110, 10);
    u8g->print("C");
}

/*
 * FUNCTION DrawNotification()
 * 
 * Sets the position and font size for the number of notifications. Displays the gramatically correct sentance 
 * for number of notifications more than 1.
 * 
 * @param (char numOfNotifications) 
 * @return (void)
 * 
 */ 
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

/*
 * FUNCTION DrawMessageSender()
 * 
 * Sets the position and font size for the sender and subject
 * and prints to the screen
 * 
 * @param (String sender, String subject)
 * @return (void)
 * 
 */ 
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
  }
  while ( u8g->nextPage() );
  delay(200);
}


