#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initialize_oled(void) {
    /* Initializes OLED for 128x64 I2C screen */    
    
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
#ifdef DEBUG_OLED
            Serial.println(F("[OLED] SSD1306 allocation failed"));
#endif
        ESP.reset();
    }  

    // Show initial display buffer contents on the screen --
    // the library initializes this with an Adafruit splash screen.
    display.display();
    delay(2000); // Pause for 2 seconds

    // Clear the buffer
    display.clearDisplay();
    delay(1000); // Pause for 1 second
}

void clear_oled(void){
    /* Clears the buffer */  
    display.clearDisplay();
}

void write_to_display(String text, int32_t x, int32_t y, int32_t text_size) {
    /* Displays Text */  
	display.setTextSize(text_size);
	display.setTextColor(WHITE);
	display.setCursor(x, y);
	display.println(text);
	display.display();
}

void scroll_text(String text, int32_t x, int32_t y, int32_t text_size) {
    /* Scrolls part of the screen */
	display.setCursor(x, y);
	display.setTextSize(text_size);
	display.println(text);
	display.display();
	display.startscrollleft(0x00, 0x0F);
    delay(1000);
}

void draw_cloud(void){
    clear_oled();
    display.drawBitmap(0, 0, cloud, 128, 64, WHITE);
    display.display();
}

void show_app_status(void) {
    clear_oled();
    write_to_display("[STATUS] Running", FIRST_COLUMN, LINE_0, T_SIZE_1);      

    if(timestamp_flag == true) {
        write_to_display("Last sent data:", FIRST_COLUMN, LINE_2, T_SIZE_1);  
        RtcDateTime currentTime = rtc.GetDateTime(); 
        char rtc_date[MAX_RTC_TIME_STR];
        char rtc_time[MAX_RTC_TIME_STR];
    
        sprintf(rtc_date, "%d/%d/%d",       
            currentTime.Month(),            
            currentTime.Day(),            
            currentTime.Year()
        );  
        sprintf(rtc_time, "%d:%d:%d",             
            currentTime.Hour(),             
            currentTime.Minute(),           
            currentTime.Second()
        );  

        write_to_display(rtc_date, FIRST_COLUMN, LINE_3, T_SIZE_1);  
        write_to_display(rtc_time, FIRST_COLUMN, LINE_4, T_SIZE_1); 
    } 
}