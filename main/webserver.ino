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
#ifdef DEBUG_WEBSERVER
    wifiManager.resetSettings();
#endif
    
    wifiManager.autoConnect("ESP_AP", "12345678"); 

    do {
        if (WiFi.status() == WL_CONNECTED) {
            blink_on_connect();
            write_to_display("[WIFI] Done", FIRST_COLUMN, LINE_5, T_SIZE_1);
#ifdef DEBUG_IP
            delay(1000);
            show_ip();       
#endif
        }  
    } while ((WiFi.status() != WL_CONNECTED));  
          
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
        delay(2000);
        timestamp_flag = false;
        show_app_status();
#ifdef DEBUG_IP
        delay(1000);
        show_ip();                 
#endif      
    }    
}

void show_ip(void) {
    clear_oled();
    String localIP = String() + WiFi.localIP()[0] + "." + WiFi.localIP()[1] + "." + WiFi.localIP()[2] + "." + WiFi.localIP()[3];
    write_to_display(localIP, FIRST_COLUMN, LINE_2, T_SIZE_1);
    Serial.print("[WIFI] "); 
    Serial.println(WiFi.localIP()); 
}