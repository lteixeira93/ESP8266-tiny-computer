#include "wifi.h"
#include "led.h"
#include "oled.h"

void initialize_wireless(void){
    /*Initializes OLED for 128x64 I2C screen*/  
    String nodeHostname = "ESP8266-Node";

    Serial.println("[WIFI] Connecting to: ");
    Serial.println(SSID);

    WiFi.hostname(nodeHostname.c_str());
    WiFi.begin(SSID, PASSWD);

    while (WiFi.status() != WL_CONNECTED)
    {
        //blink_builtin_led(1000);
        write_to_display("[WIFI] Connecting", 0, 0, 1);
        //write_to_display(SSID, 1, 0);
    }  
    digitalWrite(LED_BUILTIN, LOW);
    clear_oled();
    Serial.println("");
    
    Serial.print("[WIFI] Connected - IP Address: ");
    Serial.println(WiFi.localIP());  

    scroll_text("[WIFI] Connected", 0, 0, 1);
    //write_to_display(WiFi.localIP().toString(), 2, 2);
}