#ifndef MQTT_H_
#define MQTT_H_

#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include "wifi.h"
#include "webserver.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVER_PORT  1883
#define AIO_USERNAME    "lteixeira93"
#define AIO_KEY         "aio_Kvkx10T02pgy7yfoPncTxJYUdM0C"

/*Initializes mqtt server*/
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVER_PORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish Temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temp");
Adafruit_MQTT_Publish Humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");  

void check_mqtt_connection(void);
void publish_dht_data(float temperature, float humidity);

#endif // MQTT_H_