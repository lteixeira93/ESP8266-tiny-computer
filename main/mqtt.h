#ifndef _MQTT_H_
#define _MQTT_H_

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include "webserver.h"
#include "oled.h"
#include "debug.h"

#define AIO_SERVER          "io.adafruit.com"
#define AIO_SERVER_PORT     1883
#define AIO_USERNAME        "lteixeira93"
#define AIO_KEY             "aio_vRvG59JJ53XoHA2zDSja86btYakD"
#define MQTT_CON_RETRIES    5

void check_mqtt_connection(void);
void publish_dht_data(float temperature, float humidity);

#endif // _MQTT_H_