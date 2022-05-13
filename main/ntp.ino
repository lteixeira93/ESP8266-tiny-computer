#include "ntp.h"

char NTC_TIME[MAX_NTC_TIME_STR];
const long utcOffsetInSeconds = -10800; // NTC Offset to update RTC on the internet 

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void initialize_ntp(void){
    /* Initializes NTP Client to get time */
    timeClient.begin();
    delay(1000);    
}

const char* get_ntp_time(void){
    timeClient.update();    

#ifdef DEBUG_NTP       
        Serial.print(timeClient.getHours());
        Serial.print(":");
        Serial.print(timeClient.getMinutes());
        Serial.print(":");
        Serial.println(timeClient.getSeconds());        
#endif
    
    sprintf(NTC_TIME, "%d:%d:%d",  
        timeClient.getHours(),             
        timeClient.getMinutes(),           
        timeClient.getSeconds()
    );       
    
    return NTC_TIME;
}