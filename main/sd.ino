#include "sd.h"

void initialize_sd(void) {
    /* Initializes SD card */
    write_to_display("[SD] Done", FIRST_COLUMN, LINE_3, T_SIZE_1);
    
    if (!SD.begin(CS_PIN)) {
        Serial.println("[SD] SD Card error");
        return;
    }
    
    Serial.println("[SD] Card Initialized");   
    delay(1000);
}

void write_to_sd_card(String data) {
    /* Write to SD card */
    File dataFile;
    dataFile = SD.open("datalog.csv", FILE_WRITE);

    if (dataFile) {
        Serial.println(data);
        dataFile.println(data);  
        dataFile.close();           
    }
}