#ifndef SCREEN_H
#define SCREEN_H 

#include <DS3231.h>
#include "U8glib.h"

/*
 *  CLASS Screen
 *  
 *  This class controls the printing of information to the screen
 *  through specific methods.
 */
class Screen
{
private:
  U8GLIB_SH1106_128X64 *u8g; 
public:
       Screen(U8GLIB_SH1106_128X64* u8g){this->u8g = u8g;};
       
 /*
  * FUNCTION DrawDate()
  * 
  * Returns (void)
  * 
  * @param (String date) Date to be drawn to screen
  * @return (void)
  */
  void DrawDate(String date);

 /*
  * FUNCTION DrawTime()
  * 
  * Returns (void)
  * 
  * @param (String time) Time to be drawn to screen
  * @return (void)
  */
  void DrawTime(String time);
  
 /*
  * FUNCTION DrawTemperate()
  * 
  * Returns (void)
  * 
  * @param (int temperate) Temperature to be drawn to screen
  * @return (void)
  */
  void DrawTemperature(int temperate);

 /*
  * FUNCTION DrawNotifications()
  * 
  * Is given the number of notifcations to be drawn
  * and creates a gramatically correct sentence
  * 
  * @param (char numOfNotifications) Number
  * @return (void)
  */
  void DrawNotifications(char numOfNotifications);

 /*
  * FUNCTION DrawNotifications()
  *
  * Draws the sender of the message and subject of the message
  * to the screen.
  * 
  * @param (String sender): Name of message sender
  * @param (String subjecdt): Subject of the message
  * @return (void)
  */
  void DrawMessageSender(String sender, String subject);
};
#endif
