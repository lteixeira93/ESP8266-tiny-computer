#include "dht11.h"

DHT dht (DHT_PIN, DHT_TYPE);

float bTemperature = 0;
float bHumidity    = 0;

void initialize_dht11(void){
    /*Initializes sensor*/
    clear_oled();
    write_to_display("[DHT] Loading", 0, 0, 1);
    dht.begin();
    delay(1000);
}

float readTemperature(void){
    /*Reads temperature*/
    float temperature = dht.readTemperature();

    if(!isnan(temperature)){
        bTemperature = temperature;
        Serial.print("Current temperature = ");
        Serial.println(temperature);

        return temperature;
    }
    else{
        Serial.print("Current temperature = ");
        Serial.println(bTemperature);

        return bTemperature;
    }
}

float readHumidity(void){
    /*Reads humidity*/

    float humidity = dht.readHumidity();

    if(!isnan(humidity)){
        Serial.print("Current humidity = ");
        bHumidity = humidity;
        Serial.println(humidity);

        return humidity;
    }
    else{
        Serial.print("Current humidity = ");
        Serial.println(bHumidity);

        return bHumidity;
    }    
}