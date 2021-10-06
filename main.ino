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

void setup(){
    Serial.begin(115200);
    initialize_oled();
    initialize_rtc();    
    initialize_dht11();
    wifi_setup_webserver();
}

void loop(){    
    check_mqtt_connection();
  
    RtcDateTime currentTime = rtc.GetDateTime();

    /*Everyday at 18PM DHT11 sensor data will be sent to the cloud*/
    if (currentTime.Hour() == 18 && currentTime.Minute() == 0 && currentTime.Second() == 0)
    {
        clear_oled();
        draw_cloud();
        publish_dht_data(readTemperature(), readHumidity());
        // Save locally to SPI SDcard
        delay(1000); // Add 1 second delay to jump multiple true in if statemente in the same second
    }

    show_timestamp();
}
