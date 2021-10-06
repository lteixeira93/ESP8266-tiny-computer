#include <Wire.h>      
#include <RtcDS3231.h>
  
RtcDS3231<TwoWire> rtc(Wire);
  
void setup() {  
  Serial.begin(115200);
  rtc.Begin();
  
  RtcDateTime currentTime = RtcDateTime(__DATE__, __TIME__);
  rtc.SetDateTime(currentTime);   
}
  
void loop() {}
