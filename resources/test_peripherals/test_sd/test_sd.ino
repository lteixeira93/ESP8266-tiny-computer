#include <SPI.h>
#include <SD.h>

String dataString = "Ok";
bool writeToFlash = false;

void initialize_sd(void) {
    /*Initializes SD card*/
    clear_oled();
    write_to_display("[SD] Initializing", 0, 0, 1);
    delay(1000);

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
 
void setup() {
    Serial.begin(115200);
    initialize_sd();    
}

void loop(){
    if (writeToFlash == false)
    {
        write_to_sd_card(dataString);
        writeToFlash = true;
    }   
}