#include "oled.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initialize_oled(void){
    /*Initializes OLED for 128x64 I2C screen*/    
    
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
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
    /*Clears the buffer*/  
    display.clearDisplay();
}

void write_to_display(String text, int32_t x, int32_t y, int32_t text_size){
    /*Displays Text*/  
	display.setTextSize(text_size);
	display.setTextColor(WHITE);
	display.setCursor(x, y);
	display.println(text);
	display.display();
}

void scroll_text(String text, int32_t x, int32_t y, int32_t text_size){
    /*Scrolls part of the screen*/
	display.setCursor(x, y);
	display.setTextSize(text_size);
	display.println(text);
	display.display();
	display.startscrollleft(0x00, 0x00);
}