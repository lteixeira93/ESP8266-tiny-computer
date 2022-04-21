#include <Wire.h>   
#include <SPI.h>   
#include <RtcDS3231.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define MAX_NTC_TIME_STR 10
#define MAX_RTC_TIME_STR 20

RtcDS3231<TwoWire> rtc(Wire);

char RTC_TIME[20];
char NTC_TIME[MAX_NTC_TIME_STR];

const char *ssid     = "VIVOFIBRA-072D";
const char *password = "72231A072D";

const long utcOffsetInSeconds = -10800;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void initialize_ntp(void){
    /*Initializes NTP Client to get time*/
    WiFi.begin(ssid, password);

    while ( WiFi.status() != WL_CONNECTED ) {
      delay ( 500 );
      Serial.print ( "." );
    }

    timeClient.begin();
}

const char* get_ntp_time(void){
    timeClient.update();    
   
    sprintf(NTC_TIME, "%d:%d:%d",  
        timeClient.getHours(),             
        timeClient.getMinutes(),           
        timeClient.getSeconds()
    );       
    
    return NTC_TIME;
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
