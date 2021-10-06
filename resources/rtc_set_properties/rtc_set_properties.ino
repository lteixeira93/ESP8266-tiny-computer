#include <Wire.h>      
#include <RtcDS3231.h>
  
RtcDS3231<TwoWire> rtc(Wire);
char RTC_TIME[20];
  
void setup() {  
  Serial.begin(115200);
  rtc.Begin();
  
  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
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
