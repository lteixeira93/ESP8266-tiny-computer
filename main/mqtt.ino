#include "mqtt.h"

bool mqttConnectFlag = true;

void check_mqtt_connection(void){
    /*Handles connection to mqtt server*/
    clear_oled();
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }
    
    uint8_t retries = 5;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        #ifdef DEBUG_MQTT
            Serial.println(mqtt.connectErrorString(ret));
            Serial.println("Retrying MQTT connection in 5 seconds...");
        #endif

        mqtt.disconnect();
        delay(5000);  // wait 5 seconds
        retries--;
        if (retries == 0) {
            ESP.reset(); // TO:DO Check this
        }
    }
    #ifdef DEBUG_MQTT
        Serial.println("MQTT Connected!");
    #endif

    if (mqttConnectFlag == true)
    {
        mqttConnectFlag = false;
        clear_oled();
        write_to_display("[MQTT] Connected", 0, 0, 1);
        delay(1000);
        clear_oled();
    } 
    
}

void publish_dht_data(float temperature, float humidity){
    /*Publishes dht11 data*/
    if (! Temperature.publish(temperature)) { 
        #ifdef DEBUG_MQTT
            Serial.println(F("Temperature Failed"));
        #endif
    } else {
        #ifdef DEBUG_MQTT
            Serial.println("Temperature: "+String(temperature)+"C");
        #endif
    }
    #ifdef DEBUG_MQTT
        Serial.print(F("\nSending Humidity val "));
    #endif

    if (! Humidity.publish(humidity)) {
        #ifdef DEBUG_MQTT
            Serial.println(F("Humidity Failed"));
        #endif
    } else {
        #ifdef DEBUG_MQTT
            Serial.println("Humidity: "+String(humidity)+"%");
        #endif
    }
}