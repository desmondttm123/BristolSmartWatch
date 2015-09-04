#include "Watch.h"

Watch::Watch()
{

  //Button number 1 ************************************************************************************
  pinMode(buttonstatePin, INPUT_PULLUP);           // set pin to input
  digitalWrite(buttonstatePin, HIGH);


  //Button number 2 ************************************************************************************
  pinMode(sleepwakePin, INPUT_PULLUP);           // set pin to input
  digitalWrite(sleepwakePin, HIGH);

  // FlashLight  ************************************************************************************
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin , LOW);

  //Vibration Motor should be connected to GND  ************************************************************************************
  pinMode(vibratePin, OUTPUT);
  digitalWrite(vibratePin, LOW);

}

 
void Watch::UpdateScreen(void) 
{
  u8g.firstPage();
  do 
  {
    displayScreen.DrawNotifications(Number);
    displayScreen.DrawTime(clock.GetTime());
    displayScreen.DrawDate(clock.GetDate());
    displayScreen.DrawTemperature(clock.GetTemperature());
  }
  while ( u8g.nextPage() );
}
 
void Watch::CheckButtonState() 
{
  //Goes to notification page
  if (digitalRead(buttonstatePin) == LOW) 
  {
    delay(100);
    if (screen == 0) 
    {
      screen = 1;
    }
    else 
    {
      screen = 0;
    }
  }

  // Turns the screen off
  if (digitalRead(sleepwakePin) == LOW) 
  {
    delay(100);
    if (screensleep == 0) 
    {
      screensleep = 1;
    }
    else 
    {
      screensleep = 0;
    }
  }

  // Turns on the Flash Light
  if (screen == 1) 
  {
    digitalWrite(ledPin , HIGH);
  }
  else 
  {
    digitalWrite(ledPin, LOW);
  }
}

void Watch::CheckNotifications() 
{
  bluetoothCommunication.Read();
  
  if(bluetoothCommunication.GetNewMessage()) 
  {
    displayScreen.DrawMessageSender(bluetoothCommunication.GetName(), 
                                    bluetoothCommunication.GetSubject());
    bluetoothCommunication.SetNewMessage(false);
   
    //Time to display message
    delay(2000); 
  }
  
  int temp = bluetoothCommunication.GetNumber();
  
  if(temp != Number && temp > '0') 
  {
    digitalWrite(vibratePin, HIGH);
    delay(300);
    digitalWrite(vibratePin, LOW);
  }
  
  Number = bluetoothCommunication.GetNumber();
}


