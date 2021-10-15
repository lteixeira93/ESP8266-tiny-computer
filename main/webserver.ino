#include "webserver.h"
#include "oled.h"

void wifi_setup_webserver(void){
    /*Initializes wifi setup webserver*/
    clear_oled();
    draw_ap();
    
    #ifdef DEBUG_WEBSERVER
        wifiManager.resetSettings();
    #endif
    
    wifiManager.autoConnect("ESP_AP", "12345678"); 

    if (WiFi.status() == WL_CONNECTED)
    {
        clear_oled();
        write_to_display("[WIFI] Connected", 0, 0, 1);
        Serial.println(WiFi.localIP()); 
        digitalWrite(LED_BUILTIN, HIGH); 
        delay(2000);
        digitalWrite(LED_BUILTIN, LOW); 
    }    
}