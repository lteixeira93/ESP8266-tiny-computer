#include "ntp.h"

char NTC_TIME[MAX_NTC_TIME_STR];

void initialize_ntp(void){
    /*Initializes NTP Client to get time*/
    timeClient.begin();
    clear_oled();
    write_to_display("[NTC] Initializing", 0, 0, 1);
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