#ifndef _MQTT_H_
#define _MQTT_H_

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include "webserver.h"
#include "oled.h"
#include "debug.h"

#define AIO_SERVER          "io.adafruit.com"
#define AIO_SERVER_PORT     1883
#define AIO_USERNAME        "USER"
#define AIO_KEY             "KEY"
#define MQTT_CON_RETRIES    5

void check_mqtt_connection(void);
void publish_dht_data(unsigned char temperature, unsigned char humidity);

#endif // _MQTT_H_