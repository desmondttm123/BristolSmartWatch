#include "Clock.hpp"

String Clock::GetTime() {
      String time = "";
      int second, minute, hour, date, 
          month, year, temperature, DoW;
      second = timer.getSecond();
      minute = timer.getMinute();
      hour = timer.getHour(h12, PM);
      date = timer.getDate();
      month = timer.getMonth(Century);
      year = timer.getYear();
      temperature = timer.getTemperature();
      DoW = timer.getDoW();

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
