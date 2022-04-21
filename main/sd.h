#ifndef _SD_H_
#define _SD_H_

#include <SPI.h>
#include <SD.h>
//#include "debug.h"

#define CS_PIN 15

void initialize_sd(void);
void write_to_sd_card(String data);

#endif // _SD_H_