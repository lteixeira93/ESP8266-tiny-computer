#include "mqtt.h"

WiFiClient client;

/* Initializes mqtt server */
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVER_PORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish Humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");  

void check_mqtt_connection(void) {
    /* Handles connection to mqtt server */
    int8_t ret;

    // Stop if already connected.
    if (mqtt.connected()) {
        return;
    }
    
    uint8_t retries = MQTT_CON_RETRIES;

    while ((ret = mqtt.connect()) != 0) { // Connecting will return 0 for connected
#ifdef DEBUG_MQTT
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("[MQTT] Retrying MQTT connection in 5 seconds...");
#endif
        mqtt.disconnect();
        delay(5000);  // Wait 5 seconds to retry
        retries--;
        if (retries == 0) {
            clear_oled();
            write_to_display("[MQTT] Conn Error", FIRST_COLUMN, LINE_0, T_SIZE_1);
            Serial.println("[MQTT] Couldn't connect, restarting");
            delay(1000);
            ESP.reset();
        }
    }

#ifdef DEBUG_MQTT
        Serial.println("[MQTT] Connected");
#endif    
}

void publish_dht_data(float temperature, float humidity){
    /* Publishes DHT11 data */
    if (!Temperature.publish(temperature)) { 
#ifdef DEBUG_MQTT
        Serial.println(F("[MQTT] Temperature Failed"));
#endif
    } else {
#ifdef DEBUG_MQTT
        Serial.println("[MQTT] Temperature: "+String(temperature)+"C");
#endif
    }
#ifdef DEBUG_MQTT
        Serial.print(F("\n[MQTT] Sending Humidity val "));
#endif

    if (!Humidity.publish(humidity)) {
#ifdef DEBUG_MQTT
        Serial.println(F("[MQTT] Humidity Failed"));
#endif
    } else {
#ifdef DEBUG_MQTT
        Serial.println("[MQTT] Humidity: "+String(humidity)+"%");
#endif
    }
}