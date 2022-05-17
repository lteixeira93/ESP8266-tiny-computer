#include "dht11.h"

DHT dht (DHT_PIN, DHT_TYPE);

unsigned char bTemperature = 0;
unsigned char bHumidity    = 0;

void initialize_dht11(void){
    /* Initializes sensor */
    write_to_display("[DHT11] Done", FIRST_COLUMN, LINE_2, T_SIZE_1);
    dht.begin();
    delay(1000);
}

unsigned char readTemperature(void){
    /* Reads temperature */
    unsigned char temperature = dht.readTemperature();

    if(!isnan(temperature)){
        bTemperature = temperature;
#ifdef DEBUG_DHT
            Serial.print("[DHT11] Current temperature = ");
            Serial.println(temperature);
#endif

        return temperature;
    }
    else{
#ifdef DEBUG_DHT
            Serial.print("[DHT11] Current temperature = ");
            Serial.println(bTemperature);
#endif

        return bTemperature;
    }
}

unsigned char readHumidity(void){
    /* Reads humidity */
    unsigned char humidity = dht.readHumidity();

    if(!isnan(humidity)){
#ifdef DEBUG_DHT
            Serial.print("[DHT11] Current humidity = ");        
            Serial.println(humidity);
#endif

        bHumidity = humidity;
        
        return humidity;
    }
    else{
#ifdef DEBUG_DHT
            Serial.print("[DHT11] Current humidity = ");
            Serial.println(bHumidity);
#endif

        return bHumidity;
    }    
}