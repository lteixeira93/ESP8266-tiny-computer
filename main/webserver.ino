#include "webserver.h"
#include "oled.h"

WiFiManager wifiManager;

void blink_on_connect(void) {
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(2000);
    digitalWrite(LED_BUILTIN, LOW); 
}

void wifi_setup_webserver(void) {
    /* Initializes wifi setup webserver */
    // if (WiFi.status() != WL_CONNECTED) {
    //     clear_oled();
    //     draw_ap();
    // }    
    
#ifdef DEBUG_WEBSERVER
    wifiManager.resetSettings();
#endif
    
    wifiManager.autoConnect("ESP_AP", "12345678"); 

    if (WiFi.status() == WL_CONNECTED) {
        write_to_display("[WIFI] Done", FIRST_COLUMN, LINE_4, T_SIZE_1);
        Serial.println(WiFi.localIP()); 
        blink_on_connect();
    }    
}

void reset_wifi_setup_webserver(void) {
    clear_oled();
    write_to_display("AP ENABLED", FIRST_COLUMN, LINE_0, T_SIZE_2);
    wifiManager.resetSettings();
    wifiManager.autoConnect(AP_SSID, AP_PASS); 

    if (WiFi.status() == WL_CONNECTED) {
        blink_on_connect();

        clear_oled();
        write_to_display("[WIFI] Done", FIRST_COLUMN, LINE_0, T_SIZE_1);

        String localIP = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." + WiFi.localIP()[3];
        write_to_display(localIP, FIRST_COLUMN, LINE_2, T_SIZE_1);

        Serial.println(WiFi.localIP());         
    }    
}