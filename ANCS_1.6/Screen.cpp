#include "Screen.hpp"
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


