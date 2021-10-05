#include "mqtt.h"

void check_mqtt_connection(void){
    /*Handles connection to mqtt server*/
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }

    Serial.print("Connecting to MQTT... ");

    uint8_t retries = 5;
    while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        mqtt.disconnect();
        delay(5000);  // wait 5 seconds
        retries--;
        if (retries == 0) {
            ESP.reset();
        }
    }
    Serial.println("MQTT Connected!");
}

void publish_dht_data(float temperature, float humidity){
    /*Publishes dht11 data*/
    if (! Temperature.publish(temperature)) { 
        Serial.println(F("Temperature Failed"));
    } else {
        Serial.println("Temperature: "+String(temperature)+"C");
    }
    Serial.print(F("\nSending Humidity val "));

    if (! Humidity.publish(humidity)) {
        Serial.println(F("Humidity Failed"));
    } else {
        Serial.println("Humidity: "+String(humidity)+"%");
    }
}