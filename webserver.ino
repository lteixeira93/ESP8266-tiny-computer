#include "webserver.h"
#include "led.h"
#include "oled.h"

void initialize_webserver(void){
    /*Initializes webserver*/
    server.on("/", [] (){
        server.send(200, "Header", "Node WebServer - Home");
    });
    server.begin();
}

void wifi_setup_webserver(void){
    /*Initializes wifi setup webserver*/
    write_to_display("[WIFI] SETUP", 0, 0, 1);
    WiFiManager wifiManager;
    wifiManager.autoConnect("ESP_AP", "12345678"); 
}