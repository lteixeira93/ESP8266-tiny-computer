#ifndef WEBSERVER_H_
#define WEBSERVER_H_

#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h>
#include "wifi.h"

ESP8266WebServer server(80);
void initialize_webserver(void);
void wifi_setup_webserver(void);

#endif // WEBSERVER_H_ 

