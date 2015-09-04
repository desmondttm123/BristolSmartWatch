#include <U8glib.h>

//#include <U8glib.h>
//#include "U8glib.h"



#include "Clock.h"
#include "BluetoothCommunication.h"
#include "Screen.h"


/*
 *  CLASS Watch
 *  
 *  This class controls function that are implemented in the main code. 
 *  The Watch class acts as a bridge between the other classes and the main code
 */
class Watch
{

  private:
    /** Global variables used in code **/
    int screen = 0; //initial value
    int screensleep = 0; //initial value
    int Number; // determines the number of message and prevetns vibration motor from activating twice upon receiveing one message

    int buttonstatePin = 8; //pin 8 arduino
    int sleepwakePin = 6; //pin 6 arduino
    int vibratePin = 4; //pin 4 on arduino
    int ledPin = 5; // pin 5 on arduino


 //Driver declaration
    U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);
   

    Clock clock;
    Screen displayScreen(&u8g);
    BluetoothCommunication bluetoothCommunication(&mySerial); 
  
  public:

    /*
     * Constructor
     */
    Watch(void);
  
  /*
   * FUNCTION UpdateScreen()
   * 
   * Calls all of the appropriate methods to draw all information 
   * to the screen
   * 
   * @param (void)
   * @return (void)
   * 
   */
    void UpdateScreen(void);
  
  /*
   * FUNCTION CheckButtonState()
   * 
   * Checks the states of all the hardware buttons.
   * 
   * @param (void)
   * @return (void)
   * 
   */ 
    void CheckButtonState();

  
  /*
   * FUNCTION CheckNotifications()
   * 
   * Calls BluetoothCommuncation.Read() to read any information
   * over Bluetooth. Writes a notification to the screen if 
   * there is a new notifcation and also vibrates.
   * 
   * @param (void)
   * @return (void)
   * 
   */ 
    void CheckNotifications();

};

