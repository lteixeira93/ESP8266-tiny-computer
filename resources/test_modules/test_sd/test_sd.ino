#include <SPI.h>
#include <SD.h>

#define CS_PIN 15

File dataFile;
String dataString = "Ok";
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
    SD.begin(CS_PIN);
    dataFile = SD.open("datalog.csv", FILE_WRITE);

    if (dataFile) {
        Serial.println(data);
        dataFile.println(data);             
    }
}

void erase_sd_card(String data) {
    /*Erase data on SD card*/
    SD.begin(CS_PIN);
    SD.remove(data);

    if (SD.exists(data))
    { 
        Serial.print("Could not delete file ");
        Serial.println(data);
    }
}
 
void setup() {
    Serial.begin(115200);
    initialize_sd();    
}

void loop(){    
    if (writeToFlash == false) {
        Serial.println("[SD] Starting operation");
        //write_to_sd_card(dataString);        
        erase_sd_card("datalog.csv");
        erase_sd_card("datalog.txt");
        writeToFlash = true;
    }   
}