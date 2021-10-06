/* System includes */
#include <stdint.h>

/* Local includes */
#include "oled.h"
#include "dht11.h"
#include "mqtt.h"
#include "rtc.h"
#include "sd.h"
#include "webserver.h"
#include "debug.h"

String dataString = "";
char RTC_TIME[20];

void setup(){
    Serial.begin(115200);
    initialize_oled();
    initialize_rtc();    
    initialize_dht11();
    initialize_sd();
    wifi_setup_webserver();
}

void loop(){    
    check_mqtt_connection();
  
    RtcDateTime currentTime = rtc.GetDateTime();
    sprintf(RTC_TIME, "%d/%d/%d %d:%d:%d",       
            currentTime.Year(),            
            currentTime.Month(),            
            currentTime.Day(),              
            currentTime.Hour(),             
            currentTime.Minute(),           
            currentTime.Second()
    );

    #ifdef DEBUG_RTC
        Serial.println(RTC_TIME);
    #endif
    
    /*Everyday at 18PM DHT11 sensor data will be sent to the cloud*/
    if (currentTime.Hour() == 18 && currentTime.Minute() == 0 && currentTime.Second() == 0) {    
        // Open and Save locally to SPI SDcard
        delay(500);
        dataString = String(RTC_TIME) + " , " + String(readHumidity()) + " , " + String(readTemperature());
        write_to_sd_card(dataString);
        clear_oled();
        draw_cloud();
        publish_dht_data(readTemperature(), readHumidity());
        delay(3000); // Add 3 seconds delay to jump multiple true in if statement in the same second
        clear_oled();
        write_to_display("[STATUS] Running", 0, 0, 1);
    }
    
    #ifdef DEBUG_ESP       
        Serial.println(RTC_TIME);
        Serial.println(readHumidity());
        Serial.println(readTemperature());        
        Serial.println(dataString);
    #endif
}
