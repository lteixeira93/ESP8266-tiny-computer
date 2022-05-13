#include <DHT.h>

#define DHT_TYPE    DHT11
#define DHT_PIN     0

DHT dht (DHT_PIN, DHT_TYPE);

float bTemperature = 0;
float bHumidity    = 0;

void initialize_dht11(void){
    /* Initializes sensor */
    dht.begin();
    delay(1000);
}

float readTemperature(void){
    /* Reads temperature */
    float temperature = dht.readTemperature();

    if(!isnan(temperature)){
        bTemperature = temperature;
            Serial.print("Current temperature = ");
            Serial.println(temperature);
            delay(1000);
        return temperature;
    }
    else{
            Serial.print("Current temperature = ");
            Serial.println(bTemperature);
            delay(1000);
        return bTemperature;
    }
}

float readHumidity(void){
    /* Reads humidity */
    float humidity = dht.readHumidity();

    if(!isnan(humidity)){
            Serial.print("Current humidity = ");        
            Serial.println(humidity);
            delay(1000);
        bHumidity = humidity;
        
        return humidity;
    }
    else{
            Serial.print("Current humidity = ");
            Serial.println(bHumidity);
            delay(1000);
        return bHumidity;
    }    
}

void setup(){
    Serial.begin(115200);      
    initialize_dht11();
}

void loop(){
    readTemperature();
    readHumidity();
}
