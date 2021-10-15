/* System includes */
#include <stdint.h>

/* Local includes */
#include "oled.h"
#include "dht11.h"
#include "mqtt.h"
#include "rtc.h"
#include "sd.h"
#include "webserver.h"
#include "ntp.h"
#include "debug.h"

#define PIN_BUTTON 0 // Set push button to D3 port

char RTC_TIME[20];
String dataString = "";

/*Reset counters for AP*/
int setAPCounter = 0;

void setup(){
    Serial.begin(115200);

    /*Initializing button using internal pull up resistor*/
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    /*Flashing starting LEDs*/
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(1000);                        
    digitalWrite(LED_BUILTIN, LOW);   
    delay(1000);

    /*Initializing peripherals*/
    initialize_oled();        
    initialize_dht11();
    initialize_sd();    

    /*Initializing webserver*/
    wifi_setup_webserver();

    /*Initializing system clock*/
    initialize_ntp();
    initialize_rtc();
}

void loop(){    
    check_mqtt_connection();   

    RtcDateTime currentTime = rtc.GetDateTime(); 
   
    #ifdef DEBUG_RTC
        show_timestamp();
    #endif
    
    /*
        Everyday at a specific time using RTC, DHT11 sensor data will be sent to the cloud and also 
        reset RTC using NTP
    */
    if ((currentTime.Hour() == 10 && currentTime.Minute() == 0 && currentTime.Second() == 0) 
        || (currentTime.Hour() == 18 && currentTime.Minute() == 00 && currentTime.Second() == 0)) {    
        // Open and Save locally to SPI SDcard
        delay(500);
        dataString = String(RTC_TIME) + " , " + String(readHumidity()) + " , " + String(readTemperature());
        write_to_sd_card(dataString);
        clear_oled();
        draw_cloud();
        publish_dht_data(readTemperature(), readHumidity());
        update_rtc_ntp();
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

    if(digitalRead(PIN_BUTTON) == LOW){        
        setAPCounter++;    
        delay(1000);        
        if (setAPCounter == 5)
        {            
            wifiManager.resetSettings();
            wifi_setup_webserver();  
            check_mqtt_connection();     
        }        
    } 
    else {        
        setAPCounter = 0;    
    }
}
