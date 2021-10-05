#ifndef OLED_H_
#define OLED_H_

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128  // OLED display width, in pixels
#define SCREEN_HEIGHT   64   // OLED display height, in pixels
#define OLED_RESET      -1   // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C // See datasheet for Address; 0x3C for 128x64, 0x3D for 128x32

void initialize_oled(void);
void clear_oled(void);
void write_to_display(String text, int32_t x, int32_t y, int32_t text_size);
void scroll_text(String text, int32_t x, int32_t y, int32_t text_size);

#endif // OLED_H_