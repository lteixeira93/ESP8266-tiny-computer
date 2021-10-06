#include "wifi.h"
#include "led.h"
#include "oled.h"

void initialize_wireless(void){
    /*Initializes Wireless*/  
    clear_oled();
    String nodeHostname = "ESP8266-Node";
    
    Serial.println("[WIFI] Connecting to: ");
    Serial.println(SSID);

    WiFi.hostname(nodeHostname.c_str());
    WiFi.begin(SSID, PASSWD);
    

    while (WiFi.status() != WL_CONNECTED)
    {
        //blink_builtin_led(1000);
        write_to_display("[WIFI] Connecting", 0, 0, 1);
        //write_to_display(SSID, 0, 0, 1);
    }  
    digitalWrite(LED_BUILTIN, LOW);
    clear_oled();
    Serial.println("");
    
    Serial.print("[WIFI] Connected - IP Address: ");
    Serial.println(WiFi.localIP());  

    write_to_display("[WIFI] Connected", 0, 0, 1);
    //write_to_display(WiFi.localIP().toString(), 2, 2);
}