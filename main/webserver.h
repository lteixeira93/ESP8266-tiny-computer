#ifndef _WEBSERVER_H_
#define _WEBSERVER_H_

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266WiFi.h>
#include <WiFiManager.h>
#include "debug.h"

#define AP_SSID "ESP-AP"
#define AP_PASS "12345678"

void blink_on_connect(void);
void wifi_setup_webserver(void);
void reset_wifi_setup_webserver(void);

#endif // _WEBSERVER_H_ 