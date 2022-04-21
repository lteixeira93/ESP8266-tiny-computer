#include "sd.h"

void initialize_sd(void) {
    /*Initializes SD card*/
    clear_oled();
    write_to_display("[SD] Initializing", 0, 0, 1);
    delay(1000);

    if (!SD.begin(CS_PIN)) {
        clear_oled();
        write_to_display("[SD] SD Card error", 0, 0, 1);
        Serial.println("SD Card error");
        return;
    }
    
    clear_oled();
    write_to_display("[SD] Card Initialized", 0, 0, 1);
    Serial.println("Card Initialized");   
}

void write_to_sd_card(String data) {
    /*Write to SD card*/

    File dataFile;
    dataFile = SD.open("datalog.csv", FILE_WRITE);

    if (dataFile) {
        Serial.println(data);
        dataFile.println(data);  
        dataFile.close();           
    }
}