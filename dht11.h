#ifndef DHT11_H_
#define DHT11_H_

#include <DHT.h>
#include "debug.h"

#define DHT_TYPE    DHT11
#define DHT_PIN     14 // D5

void initialize_dht11(void);
float readTemperature(void);
float readHumidity(void);

#endif // DHT11_H_