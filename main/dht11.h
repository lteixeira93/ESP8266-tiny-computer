#ifndef _DHT11_H_
#define _DHT11_H_

#include <DHT.h>
#include "debug.h"

#define DHT_TYPE    DHT11
#define DHT_PIN     2

void initialize_dht11(void);
float readTemperature(void);
float readHumidity(void);

#endif // _DHT11_H_