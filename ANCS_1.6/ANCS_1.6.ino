//#include <U8glib.h>

#include <U8glib.h>

#include <SoftwareSerial.h>

#include <DS3231.h>
#include <Wire.h>
#include "Arduino.h"
#include "Watch.h"



/*
 *For The older versions of the Watch, it is (10,16). All later boards
 *Uses (10,11) as the serial
 */
SoftwareSerial mySerial(10, 11); // RX, TX


/** Instanciate Watch **/

Watch watch;


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
  /* Need to experiment with where these sit */
  
  //leave these two in for the moment
  Wire.begin();
  Serial.begin(9600);
  //leave these two in for the moment
  mySerial.begin(9600);

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
  watch.CheckButtonState();  
  watch.UpdateScreen();
  watch.CheckNotifications(); 
}

