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

/* Specify time to send sensor data to Adafruit cloud */
#define HOUR      19
#define MINUTE    49
#define SECOND    45

static void start(void);
static void button_reset(void);
static void sensor_data_sender(void);

void setup(void){
    Serial.begin(115200);
    start();
}

void loop(void){    
    Serial.println(timestamp_flag);
    button_reset();
    check_mqtt_connection();    
    sensor_data_sender();    
}

static void start(void) {
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
    RtcDateTime currentTime = rtc.GetDateTime(); 

    String dataString = "";

#ifdef DEBUG_RTC
    show_timestamp();
#endif 

    sprintf(rtc_time, "%d/%d/%d %d:%d:%d",       
        currentTime.Month(),            
        currentTime.Day(),            
        currentTime.Year(),            
        currentTime.Hour(),             
        currentTime.Minute(),           
        currentTime.Second()
    );

    /* DHT11 sensor data will be sent to adafruit cloud */
    if (currentTime.Hour() == HOUR && currentTime.Minute() == MINUTE && currentTime.Second() == SECOND) {    
        timestamp_flag = true;
        dataString = String(rtc_time) + ";" + String(readHumidity()) + ";" + String(readTemperature()) + ";";
        draw_cloud();   
        delay(2000);     
        write_to_sd_card(dataString);        
        publish_dht_data(readTemperature(), readHumidity());
        show_app_status();
        update_rtc_ntp();              
    }
   
#ifdef DEBUG_ESP       
    Serial.println(readHumidity());
    Serial.println(readTemperature());    
    dataString = String(rtc_time) + ";" + String(readHumidity()) + ";" + String(readTemperature()) + ";";    
    Serial.println(dataString);
    delay(1000);
#endif
}