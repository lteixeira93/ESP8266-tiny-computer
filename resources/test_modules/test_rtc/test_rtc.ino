#include <Wire.h>   
#include <SPI.h>   
#include <RtcDS3231.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string.h>

#define MAX_NTC_TIME_STR 15
#define MAX_RTC_TIME_STR 25

RtcDS3231<TwoWire> rtc(Wire);

char rtc_time[MAX_RTC_TIME_STR];
char ntc_time[MAX_NTC_TIME_STR];

const char *ssid     = "SSID";
const char *password = "PASS";

const long utcOffsetInSeconds = -10800;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void initialize_ntp(void){
    /* Initializes NTP Client to get time */
    WiFi.begin(ssid, password);

    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }

    timeClient.begin();
}

const char* get_ntp_time(void){
    timeClient.update();    
   
    sprintf(ntc_time, "%d:%d:%d",  
        timeClient.getHours(),             
        timeClient.getMinutes(),           
        timeClient.getSeconds()
    );       

    return ntc_time;
}
  
void setup() {  
  Serial.begin(115200);
  initialize_ntp();
  rtc.Begin();
  
  RtcDateTime currentTime = RtcDateTime(__DATE__, get_ntp_time());
  rtc.SetDateTime(currentTime);   
}
  
void loop() {
  RtcDateTime currentTime = rtc.GetDateTime();
  
  sprintf(rtc_time, "%d/%d/%d %d:%d:%d",       
          currentTime.Year(),            
          currentTime.Month(),            
          currentTime.Day(),              
          currentTime.Hour(),             
          currentTime.Minute(),           
          currentTime.Second()
  );

  rtc_time[strlen(rtc_time) + 1] = '\0';
  Serial.println(rtc_time);
}
