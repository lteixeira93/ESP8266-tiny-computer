#include "dht11.h"

DHT dht (DHT_PIN, DHT_TYPE);

float bTemperature = 0;
float bHumidity    = 0;

void initialize_dht11(void){
    /*Initializes sensor*/
    clear_oled();
    write_to_display("[DHT11] Initializing", 0, 0, 1);
    dht.begin();
    delay(1000);
}

float readTemperature(void){
    /*Reads temperature*/
    float temperature = dht.readTemperature();

    if(!isnan(temperature)){
        bTemperature = temperature;
        #ifdef DEBUG_DHT
            Serial.print("Current temperature = ");
            Serial.println(temperature);
        #endif

        return temperature;
    }
    else{
        #ifdef DEBUG_DHT
            Serial.print("Current temperature = ");
            Serial.println(bTemperature);
        #endif

        return bTemperature;
    }
}

float readHumidity(void){
    /*Reads humidity*/

    float humidity = dht.readHumidity();

    if(!isnan(humidity)){
        #ifdef DEBUG_DHT
            Serial.print("Current humidity = ");        
            Serial.println(humidity);
        #endif

        bHumidity = humidity;
        
        return humidity;
    }
    else{
        #ifdef DEBUG_DHT
            Serial.print("Current humidity = ");
            Serial.println(bHumidity);
        #endif

        return bHumidity;
    }    
}