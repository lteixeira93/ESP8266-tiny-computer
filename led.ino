#include "led.h"

void blink_builtin_led(int32_t timeBlink){
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(timeBlink);                        
  digitalWrite(LED_BUILTIN, LOW);   
  delay(timeBlink);
}