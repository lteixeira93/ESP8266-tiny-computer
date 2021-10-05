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

int64_t now = millis();
int64_t lastMeasure = 0;

void setup(){
    Serial.begin(115200);
    initialize_oled();
    initialize_dht11();
    initialize_wireless();
    initialize_webserver();
    //wifi_setup_webserver();
}

void loop(){
    server.handleClient();
    check_mqtt_connection();
    now = millis(); // TO-DO: Must be replaced by RTC time

    if(now - lastMeasure > 5000){
        lastMeasure = now;
        Serial.println(readTemperature());
        Serial.println(readHumidity());
        publish_dht_data(readTemperature(), readHumidity());
    }    
}
