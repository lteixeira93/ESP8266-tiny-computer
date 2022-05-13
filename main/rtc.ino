#include "rtc.h"
#include "ntp.h"

void initialize_rtc(void){
    /* Initializes RTC */
    write_to_display("[RTC] Done", FIRST_COLUMN, LINE_4, T_SIZE_1);
    rtc.Begin();   
    RtcDateTime currentTime = RtcDateTime(__DATE__, get_ntp_time());
    rtc.SetDateTime(currentTime);
    delay(2000);
    show_app_status();
}

void show_timestamp(void){
    /* Show RTC properties */
    RtcDateTime currentTime = rtc.GetDateTime(); 
    char rtc_time[MAX_RTC_TIME_STR];
  
    sprintf(rtc_time, "%d/%d/%d %d:%d:%d",       
        currentTime.Year(),            
        currentTime.Month(),            
        currentTime.Day(),              
        currentTime.Hour(),             
        currentTime.Minute(),           
        currentTime.Second()
    );

    Serial.println(rtc_time);
}

void update_rtc_ntp(void){
    RtcDateTime currentTime = RtcDateTime(__DATE__, get_ntp_time());
    rtc.SetDateTime(currentTime);
}