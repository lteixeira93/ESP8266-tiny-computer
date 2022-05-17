#ifndef _DHT11_H_
#define _DHT11_H_

#include <DHT.h>
#include "debug.h"
#include "oled.h"

#define DHT_TYPE    DHT11
#define DHT_PIN     0

void initialize_dht11(void);
unsigned char readTemperature(void);
unsigned char readHumidity(void);

#endif // _DHT11_H_