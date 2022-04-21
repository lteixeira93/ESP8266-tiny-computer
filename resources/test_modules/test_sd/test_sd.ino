#include <SPI.h>
#include <SD.h>

#define CS_PIN   15
#define ERASE_SD 0

bool writeToFlash = false;

void initialize_sd(void) {
    /*Initializes SD card*/
    Serial.println("Initializing");
    if (!SD.begin(CS_PIN)) {
        Serial.println("SD Card error");
        return;
    }
    
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

void erase_sd_card(String data) {
    /*Erase data on SD card*/
    SD.remove(data);

    if (SD.exists(data)) { 
        Serial.print("Could not delete file ");
        Serial.println(data);
    }
    else {
        Serial.println(data + " erased");
    }
}
 
void setup() {
    Serial.begin(115200);
    initialize_sd();    
}

void loop(){    
    if (writeToFlash == false) {
        Serial.println("[SD] Starting operation");
        String dataString = String(1) + ";" + String(2) + ";" + String(3) + ";";
            
        if (ERASE_SD) {
            erase_sd_card("datalog.csv");
        }
        else {
            write_to_sd_card(dataString);  
        }

        writeToFlash = true;
    }   
}