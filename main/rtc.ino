#include "rtc.h"

void initialize_rtc(void){
    /*Initializes RTC*/
    clear_oled();
    write_to_display("[RTC] Initializing", 0, 0, 1);
    rtc.Begin();
    delay(1000);
}

void show_timestamp(void){
    /*Show RTC properties*/
    RtcDateTime currentTime = rtc.GetDateTime(); 
    char RTC_TIME[20];
  
    sprintf(RTC_TIME, "%d/%d/%d %d:%d:%d",       
            currentTime.Year(),            
            currentTime.Month(),            
            currentTime.Day(),              
            currentTime.Hour(),             
            currentTime.Minute(),           
            currentTime.Second()
    );
    
    Serial.println(RTC_TIME);
}