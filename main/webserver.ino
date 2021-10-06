#include "webserver.h"
#include "led.h"
#include "oled.h"

void wifi_setup_webserver(void){
    /*Initializes wifi setup webserver*/
    clear_oled();
    draw_ap();
    WiFiManager wifiManager;

    #ifdef DEBUG_WEBSERVER
        wifiManager.resetSettings();
    #endif
    
    wifiManager.autoConnect("ESP_AP", "12345678"); 

    if (WiFi.status() == WL_CONNECTED)
    {
        clear_oled();
        write_to_display("[WIFI] Connected", 0, 0, 1);
        Serial.println(WiFi.localIP()); 
        delay(1000);
    }    
}