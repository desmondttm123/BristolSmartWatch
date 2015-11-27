#include <SoftwareSerial.h>
#include "U8glib.h"
#include <DS3231.h>
#include <Wire.h>
#include "Clock.h"
#include "BluetoothCommunication.h"

const int arduinoLED = 17;

int screen = 0;
int screensleep = 0;
int buttonstate = 8;
int sleepwake = 6;
int tiltscreen = 5;
int vibrate = 4;
int led = 9;
int Number;
int sensorPin = A0;
float sensorValue = 0;

// Decleration for RTC
Clock clock; 

// Decleration for screen
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); 

// Decleration for bluetooth
SoftwareSerial mySerial(10, 16); // RX, TX

BluetoothCommunication bluetoothCommunication(&mySerial); 

/*
 * Calls all of the appropriate methods to draw all information 
 * to the screen
 */ 
void DrawScreen(void) {
  u8g.firstPage();
  do {
    DrawNotifications(Number); // Prints whether there are notifications
    DrawTime(clock.GetTime()); // Draws the time returned from the clock
    DrawDate(clock.GetDate()); // Draws the date returned from the clock
    DrawTemperature(clock.GetTemperature()); // Draws the temperature returned from the clock
    // DrawImages(); // Draws the images to the screen
    DrawBatteryStatus();
  }
  while ( u8g.nextPage() );
}

/*
 * Configures all of the states of the hardware. Not important, so do not change.
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
 * Checks the states of all the hardware buttons. Not important, so do not change.
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
 * Calls BluetoothCommuncation.Read() to read any information
 * over Bluetooth. Writes a notification to the screen if 
 * there is a new notifcation and also vibrates. Not important, so do not change.
 */ 
void BluetoothCommunications() {
  bluetoothCommunication.Read();
  
  if(bluetoothCommunication.GetNewMessage()) {
    DrawMessageSender(bluetoothCommunication.GetName(), 
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
 * Makes appropriate function calls each time it is called
 * by the arduino 
 */ 
void loop() 
{
  checkButtons();  
  DrawScreen();
  BluetoothCommunications(); 
}

/*************************************************************************************************************************/
/***************************************** Configuration Functions *******************************************************/

/*
 * Sets the position and font size for the time and
 * draws time to screen.
 */ 
void DrawTime(String time) {
    u8g.setFont(u8g_font_10x20); // Font used to draw the time. Replace the text in brackets for a new font.
    u8g.setPrintPos(18, 40); // Sets the position of the time on the screen. Left top corner is 0,0 and first number is x position.
    u8g.print(time); // Prints the time to the screen. Comment out if you do not want the time displayed.
}

/*
 * Sets the position and font size for the Date
 * and draws to screen.
 */ 
void DrawDate(String date) {
    u8g.setFont(u8g_font_5x7); // Sets the font for the date. Replace the text in brackets for a new font.
    u8g.setPrintPos(25, 50); // Sets the position of the date on the screen. Left top corner is 0,0 and first number is x position.
    u8g.print(date); // Prints the date to the screen. Comment out if you do not want the date displayed.
}

/*
 * Sets the position and font size for the temperature
 * and draws to screen.
 */ 
void DrawTemperature(int temperature) {
    /*
     * User could implement function to display the temperature in kelvin or fahrenheit.
     */
    u8g.setPrintPos(95, 10); // Position of the number part of the temperature.
    u8g.print(temperature); // Prints the number part of the temperature. Comment out if you do not want the temperature displayed.
    u8g.setPrintPos(105, 6); // Position of small circle between number part of the temperature and C.
    u8g.print("."); // Comment out if you do not want the dot displayed.
    u8g.setPrintPos(110, 10); // Position of the C in the temperature.
    u8g.print("C"); // Comment out if you do not want the time displayed.
}

/*
 * Sets the position and font size for the number of notifications. Displays the gramatically correct sentance 
 * for number of notifications more than 1. Not important, so do not change.
 */ 
void DrawNotifications(char numOfNotifications) {
  if (numOfNotifications != '0') { // Check to make sure there are notifications available.
    u8g.setFont(u8g_font_5x7); // Font used for notification text. Change text in brackets for new font.
    u8g.setPrintPos(0, 10); // Position of number of notifications.
    u8g.print(numOfNotifications); // Prints number of notifications.
    u8g.setPrintPos(10, 10); // Sets new position for New Notification text.
    if (numOfNotifications == '1') { // Check to see if there is 1 notification
      u8g.print("New Notification"); // Display notification
    }
    else {
      u8g.print("New Notifications"); // Display notifications
    }
  }
}

/*
 * Sets the position and font size for the sender and subject
 * and prints to the screen. Not important, so do not change.m                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
 */ 
void DrawMessageSender(String sender, String subject) {
  u8g.firstPage();
  do {
    //Print Message Sender
    u8g.setFont(u8g_font_5x7); // Font used for message information
    u8g.setPrintPos(0, 10); // Position of from text
    u8g.print("From : ");
    u8g.setPrintPos(30, 10); // Position of sender name
    u8g.print(sender);
    //Print Message Subject
    u8g.setPrintPos(0, 20); // Position of notification subject
    u8g.print(subject);
  }
  while ( u8g.nextPage() );
  delay(200);
}


/*
 * Function to draw the battery status
 */
void DrawBatteryStatus(){
    sensorValue = analogRead(sensorPin);
    u8g.setPrintPos(55,20);
    u8g.print(sensorValue);
    
    //changed from voltage to %
    sensorValue = ((sensorValue-530)/135)*100; 
    u8g.setPrintPos(90,20);
    u8g.print("[");
    u8g.setPrintPos(110,20);
    u8g.print("]");

    // Battery has more than 40%
    if(sensorValue >=40){
        u8g.setPrintPos(95,20);
        u8g.print("|||");
    }

    // Battery has between 40% and 20%
    if(sensorValue >=20 && sensorValue < 40 ){
        u8g.setPrintPos(100,20);
        u8g.print("||");
    }

    // Battery has between 5% and 20%
    if(sensorValue >=5 && sensorValue < 20 ){
        u8g.setPrintPos(105,20);
        u8g.print("|");
        u8g.setPrintPos(80,30);
        u8g.print("Recharge");
    }
  
  
    if(sensorValue<5){
        digitalWrite(sleepwake,LOW);  
        u8g.setPrintPos(80,30);
        u8g.print("USB Mode");
    }
}

// Image width. Update this value when adding a new image.
#define u8g_logo_width 38
// Image height. Update this value when adding a new image.
#define u8g_logo_height 24

/* 
 * Image data taken from file. To load a new image:
 *   1) Find a black and white image online and save it to the hard drive.
 *   2) Open the saved image on gimp.
 *   3) Select image from the menu at the top of the window and select Scale image...
 *   4) Change the image width and image height so it is smaller than or equal to a 64x64 image and click scale.
 *   5) Select file from the menu at the top and click export.
 *   6) Choose where to save the file and from the menu at the bottom labeled All export images select X BitMap Image (*.xbm *.icon *.bitmap)
 *   7) Open the file using your favorite text editor. Copy the data located between the curly brackets {} and paste it in the array below, removing the previous data.
 *   8) Update the image sizes above in #define u8g_logo_width and #define u8g_logo_height
 */
static unsigned char u8g_logo_bits[] U8G_PROGMEM = {
   0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xe0, 0xe0,
   0xff, 0xff, 0x3f, 0xe3, 0xe1, 0xff, 0xff, 0x3f, 0xf3, 0xf1, 0xff, 0xff,
   0x3f, 0xf3, 0xf1, 0xfe, 0xbf, 0x37, 0xf3, 0x11, 0x1c, 0x1f, 0x30, 0xf3,
   0x01, 0x08, 0x8c, 0x20, 0xf3, 0x01, 0x00, 0xc0, 0x39, 0xf3, 0x81, 0xc7,
   0xc1, 0x39, 0xf3, 0xc1, 0xc7, 0xc9, 0x38, 0xf3, 0xc1, 0xc3, 0x19, 0x3c,
   0xe3, 0x89, 0x01, 0x98, 0x3f, 0xc7, 0x18, 0x00, 0x08, 0x3e, 0x0f, 0x3c,
   0x70, 0x1c, 0x30, 0x3f, 0xff, 0xfc, 0x87, 0x31, 0xff, 0xff, 0xbf, 0xc7,
   0x23, 0x01, 0x00, 0x00, 0xc6, 0x23, 0x03, 0x00, 0x00, 0x0e, 0x30, 0xff,
   0xff, 0x3f, 0x1f, 0x3c, 0xff, 0xff, 0x3f, 0xff, 0x3f, 0xff, 0xff, 0x3f,
   0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0x3f };


/*
 * Draws the images to the screen.
 */
void DrawImages(void) {
  // graphic to draw the image to the screen. First two parameters are x,y position on the screen. Third and fourth are image width and height. Fifth is the image data.
  u8g.drawXBMP( 0, 0, u8g_logo_width, u8g_logo_height, u8g_logo_bits);
}



/*************************************************************************************************************************/


