/* System includes */
#include <stdint.h>
#include <stdbool.h>

/* Local includes */
#include "oled.h"
#include "dht11.h"
#include "mqtt.h"
#include "rtc.h"
#include "sd.h"
#include "webserver.h"
#include "ntp.h"
#include "debug.h"

/* Defines */
#define PIN_BUTTON           2  // Setting push button to D4 port
#define BUTTON_HOLD_DELAY    5  // Hold button time to reset network configurations

static void start_services(void);
static void button_reset(void);
static void sensor_data_sender(void);

void setup(void){
    Serial.begin(115200);
    start_services();
}

void loop(void){    
    button_reset();
    check_mqtt_connection();    
    sensor_data_sender();    
}

static void start_services(void) {
    /* Initializing button using internal pull up resistor */
    pinMode(PIN_BUTTON, INPUT_PULLUP);

    /* Flashing starting LEDs */
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(500);                        
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);
    digitalWrite(LED_BUILTIN, HIGH);   
    delay(500);                        
    digitalWrite(LED_BUILTIN, LOW);   
    delay(500);

    /* Initializing peripherals */    
    initialize_oled();      

    write_to_display("STATUS", FIRST_COLUMN, LINE_0, T_SIZE_2);
    delay(1000);

    initialize_dht11();
    initialize_sd();    

    /* Initializing webserver */
    wifi_setup_webserver();

    /* Initializing system clock */
    initialize_ntp();
    initialize_rtc();
}

static void button_reset(void) {
    /* Reset counters for AP */
    static int setAPCounter = 0;

    if(digitalRead(PIN_BUTTON) == LOW) {        
        setAPCounter++;    
        delay(1000);
        if (setAPCounter == BUTTON_HOLD_DELAY) {                            
            reset_wifi_setup_webserver();  
            check_mqtt_connection();     
        }        
    } 
    else {        
        setAPCounter = 0;    
    }
}

static void sensor_data_sender(void) {
    char rtc_time[MAX_RTC_TIME_STR];
    String dataString = "";

    RtcDateTime currentTime = rtc.GetDateTime(); 

#ifdef DEBUG_RTC
    show_timestamp();
#endif

    /* DHT11 sensor data will be sent to adafruit cloud and also reset RTC using NTP - TO:DO Need Fix */
    if ((currentTime.Hour() == 10 && currentTime.Minute() == 0 && currentTime.Second() == 0) 
        ||
        (currentTime.Hour() == 18 && currentTime.Minute() == 0 && currentTime.Second() == 0)) 
    {    
        // Saving locally on SD card
        delay(500);
        dataString = String(rtc_time) + " , " + String(readHumidity()) + " , " + String(readTemperature());
        write_to_sd_card(dataString);
        clear_oled();
        draw_cloud();
        publish_dht_data(readTemperature(), readHumidity());
        update_rtc_ntp();
        delay(3000); // Add 3 seconds delay to jump multiple true in if statement in the same second TO:DO Remove delay
        clear_oled();
        write_to_display("[STATUS] Running", 0, 0, 1);
    }
   
#ifdef DEBUG_ESP       
    Serial.println(readHumidity());
    Serial.println(readTemperature());        
    Serial.println(dataString);
    delay(1000);
#endif
}