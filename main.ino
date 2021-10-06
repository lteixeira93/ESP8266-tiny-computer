/* System includes */
#include <stdint.h>

/* Local includes */
#include "oled.h"
#include "dht11.h"
#include "mqtt.h"
#include "rtc.h"
#include "sd.h"
#include "webserver.h"
#include "wifi.h"

void setup(){
    Serial.begin(115200);
    initialize_oled();
    initialize_rtc();    
    initialize_dht11();
    //initialize_wireless();
    initialize_webserver();
    wifi_setup_webserver();
}

void loop(){
    server.handleClient();
    check_mqtt_connection();
  
    RtcDateTime currentTime = rtc.GetDateTime();

    /*Everyday at 8PM DHT11 sensor dat will be sent to the cloud*/
    if (currentTime.Hour() == 18 && currentTime.Minute() == 0 && currentTime.Second() == 0)
    {
        // Oled "Show Cloud Icon"
        clear_oled();
        write_to_display("[MQTT] DHT11 DATA SENT", 0, 0, 1);
        publish_dht_data(readTemperature(), readHumidity());
        delay(1000); // Add 1 second delay to jump multiple true in if statemente in the same second
    }

    show_timestamp();
}
