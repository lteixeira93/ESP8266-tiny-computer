#include "rtc.h"
#include "ntp.h"

void initialize_rtc(void){
    /*Initializes RTC*/
    clear_oled();
    write_to_display("[RTC] Initializing", 0, 0, 1);
    rtc.Begin();
    RtcDateTime currentTime = RtcDateTime(__DATE__, get_ntp_time());
    rtc.SetDateTime(currentTime);
    delay(1000);
}

void show_timestamp(void){
    /*Show RTC properties*/
    RtcDateTime currentTime = rtc.GetDateTime(); 
    char RTC_TIME[MAX_RTC_TIME_STR];
  
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

void update_rtc_ntp(void){
    RtcDateTime currentTime = RtcDateTime(__DATE__, get_ntp_time());
    rtc.SetDateTime(currentTime);
}