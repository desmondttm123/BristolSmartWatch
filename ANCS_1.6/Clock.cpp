#include "Clock.h"

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
    else if(DoW == 1)
        string+="Mon";
    else if(DoW == 2)
        string+="Tue";
    else if(DoW == 3)
        string+="Wed";       
    else if(DoW == 4)
        string+="Thu";
    else if(DoW == 5)
        string+="Fri";
    else if(DoW == 6)
        string+="Sat";
    string+=" ";
    string+=date;
    string+=" ";
    if(month == 1)
        string+="January";
    else if(month == 2)
        string+="Febuary";
    else if(month == 3)
        string+="March";
    else if(month == 4)
        string+="April"; 
    else if(month == 5)
        string+="May";  
    else if(month == 6)
        string+="June";
    else if(month == 7)
        string+="July";
    else if (month == 8)
        string+="August"; 
    else if(month == 9)
        string+="September";  
    else if(month == 10)
        string+="October";  
    else if(month == 11)
        string+="November"; 
    else if(month == 12)
        string+="December";

    return string;
}

int Clock::GetTemperature() {
    return timer.getTemperature();
}
