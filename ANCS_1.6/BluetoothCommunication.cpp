#include "BluetoothCommunication.hpp"
String BluetoothCommunication::Read() {
  while (mySerial->available()) {
    char c = (char)mySerial->read();

    if ((int)c != 0) {
      buffer += c;
    }

    if (buffer.indexOf("OK+ANCS:") == 15) {  
      temp =  buffer.substring(26); // temp contains all the unclean data that needs to be edited
      int ending = temp.indexOf("OK+ANC");
      String data = temp.substring(1, ending); // contains the first part is name followed by message
      String data2 = temp.substring(ending+10);// contains second part of message with ANCS, needs to be filtered again

      if (!mySerial->available()) {
        if (UID == false) {
          Name = data;
        } else if (UID ==true){
          Subject2 = data+data2;
        }

        int length = parsedSubject2.length();
        if (length >= 1) {
          Subject2 = parsedSubject2.substring(0, length);
        }

        Line1 = Subject2.substring(0, 15);
        Line2 = Subject2.substring(15);

        //displayScreen->DrawMessageSender(Name, Subject2);
        buffer = "";
        if(printed == true) {
          mySerial->write(Message);
          printed = false;
          UID = true;
          Display = false;
        } else {
          printed = true;
          UID = false;
          delay(2000); // delay for when the message appears
          Display = true;
        }

        /*if (Display == false) {
          digitalWrite(vibrate, HIGH);
          delay(300);
          digitalWrite(vibrate, LOW);
        } else {
          digitalWrite(vibrate, LOW);
        }*/
      }
    }

    if (ANCS8SIZE > buffer.length()) {
      return "";
    }

    int indexANCS8 = buffer.indexOf("OK+ANCS8");
    boolean complete = (indexANCS8 + ANCS8SIZE) <= buffer.length();

    if(indexANCS8 != -1 && complete) {
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

      strncpy(Title, "AT+ANCS", 7);
      strncpy(&Title[7], &string.c_str()[12],4);
      strncpy(&Title[11], "122", 3);

      strncpy(Message, "AT+ANCS", 7);
      strncpy(&Message[7], &string.c_str()[12],4);
      strncpy(&Message[11], "392", 3);

      mySerial->write(Title);
    }
  }
}
