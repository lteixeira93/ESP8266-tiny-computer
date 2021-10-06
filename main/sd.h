#ifndef SD_H_
#define SD_H_

#include <SPI.h>
#include <SD.h>
//#include "debug.h"

#define CS_PIN 15
File dataFile;

void initialize_sd(void);
void write_to_sd_card(String data);

#endif // SD_H_