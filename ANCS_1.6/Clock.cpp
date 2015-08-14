#include "Clock.hpp"

String Clock::GetTime() {
      String time = "";
      int second, minute, hour, 
          month, year, temperature;
      second = timer.getSecond();
      minute = timer.getMinute();
      hour = timer.getHour(h12, PM);
      year = timer.getYear();
      temperature = timer.getTemperature();

      if(hour<10){
        time+="0"+hour;
      } else{
        time+=hour;
      }
      time+=":";
      if(minute < 10) {
        time+="0";
        time+=minute;
      }
      else {
        time+=minute;
      }
      return time;
}

String Clock::GetDate() {
    String string = "";
    int date = timer.getDate();
    int DoW = timer.getDoW();
    int month = timer.getMonth(Century);
    if (DoW == 7)
        string="Sun";
    if (DoW == 1)
        string+="Mon";
    if (DoW == 2)
        string+="Tue";
    if (DoW == 3)
        string+="Wed";       
    if (DoW == 4)
        string+="Thu";
    if (DoW == 5)
        string+="Fri";
    if (DoW == 6)
        string+="Sat";
    string+=" ";
    string+=date;
    string+=" ";
    if (month == 1)
        string+="January";
    if (month == 2)
        string+="Febuary";
    if (month == 3)
        string+="March";
    if (month == 4)
        string+="April"; 
    if (month == 5)
        string+="May";  
    if (month == 6)
        string+="June";
    if (month == 7)
        string+="July";
    if (month == 8)
        string+="August"; 
    if (month == 9)
        string+="September";  
    if (month == 10)
        string+="October";  
    if (month == 11)
        string+="November"; 
    if (month == 12)
        string+="December";

    return string;
}

int Clock::GetTemperature() {
    return timer.getTemperature();
}
