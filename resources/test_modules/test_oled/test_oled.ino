#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH    128  // OLED display width, in pixels
#define SCREEN_HEIGHT   64   // OLED display height, in pixels
#define OLED_RESET      -1   // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C // See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
#define DEBUG_SCREEN

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()   
{                
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
	Serial.println(F("SSD1306 allocation failed"));
	for(;;);
	}  

	Serial.println("Starting...");

	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
	display.display();
	delay(2000); // Pause for 2 seconds

	// Clear the buffer
	display.clearDisplay();

#ifdef DEBUG_SCREEN 
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("[DEBUG] 1");
	// display.setCursor(0,10);
	// display.println("[DEBUG] 2");
	display.setCursor(0,20);
	display.println("[DEBUG] 3");
	display.setCursor(0,30);
	display.println("[DEBUG] 4");
	display.setCursor(0,40);
	display.println("[DEBUG] 5");
	display.setCursor(0,50);
	display.println("[DEBUG] 6");
	display.setCursor(0,60);
	display.display();
	delay(2000);
	// display.clearDisplay();
	// display.setCursor(28,28);
	// display.setTextSize(1);
	// display.println("Running");
	// display.display();
	// display.startscrollright(0x00, 0x0F);
	// delay(5000);
#else
	// Display Text
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,28);
	display.println("Hello world!");
	display.display();
	delay(2000);
	display.clearDisplay();

	// Display Inverted Text
	display.setTextColor(BLACK, WHITE); // 'inverted' text
	display.setCursor(0,28);
	display.println("Hello world!");
	display.display();
	delay(2000);
	display.clearDisplay();

	// Changing Font Size
	display.setTextColor(WHITE);
	display.setCursor(0,24);
	display.setTextSize(2);
	display.println("Hello!");
	display.display();
	delay(2000);
	display.clearDisplay();

	// Display Numbers
	display.setTextSize(1);
	display.setCursor(0,28);
	display.println(123456789);
	display.display();
	delay(2000);
	display.clearDisplay();

	// Specifying Base For Numbers
	display.setCursor(0,28);
	display.print("0x"); display.print(0xFF, HEX); 
	display.print("(HEX) = ");
	display.print(0xFF, DEC);
	display.println("(DEC)"); 
	display.display();
	delay(2000);
	display.clearDisplay();

	// Display ASCII Characters
	display.setCursor(0,24);
	display.setTextSize(2);
	display.write(3);
	display.display();
	delay(2000);
	display.clearDisplay();

	// Scroll full screen
	display.setCursor(0,0);
	display.setTextSize(1);
	display.println("Full");
	display.println("screen");
	display.println("scrolling!");
	display.display();
	display.startscrollright(0x00, 0x07);
	delay(2000);
	display.stopscroll();
	delay(1000);
	display.startscrollleft(0x00, 0x07);
	delay(2000);
	display.stopscroll();
	delay(1000);    
	display.startscrolldiagright(0x00, 0x07);
	delay(2000);
	display.startscrolldiagleft(0x00, 0x07);
	delay(2000);
	display.stopscroll();
	display.clearDisplay();

	// Scroll part of the screen
	display.setCursor(0,0);
	display.setTextSize(1);
	display.println("Scroll");
	display.println("some part");
	display.println("of the screen.");
	display.display();
	display.startscrollright(0x00, 0x00);
	delay(2000);
	display.stopscroll();
	display.clearDisplay();

	// Pixel	
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Pixel");
	display.drawPixel(64, 32, WHITE);
	display.display();
	delay(2000);
	display.clearDisplay();

	// Line
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Line");
	display.drawLine(0, 20, 127, 60, WHITE);
	display.display();
	delay(2000);
	display.clearDisplay();

	// Rectangle curved corner
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Curved corner");
	display.drawRoundRect(0, 17, 60, 40, 8, WHITE);
	display.fillRoundRect(64, 17, 60, 40, 8, WHITE);
	display.display();
	delay(2000);
	display.clearDisplay();

	// Circle
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Circle");
	display.drawCircle(20, 37, 20, WHITE); 
	display.fillCircle(84, 37, 20, WHITE);
	display.display();
	delay(2000);
	display.clearDisplay();

	// Triangle
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Triangle");
	display.drawTriangle(30, 17, 0, 62, 60, 62, WHITE);
	display.fillTriangle(94, 17, 64, 62, 124, 62, WHITE); 
	display.display();
	delay(2000);
	display.clearDisplay();

	// Invert
	display.invertDisplay(true);
	display.setTextSize(1);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("Inverted");
	display.drawCircle(30, 37, 20, WHITE);
	display.drawRoundRect(64, 17, 60, 40, 8, WHITE); 
	display.display();
	delay(3000);
	display.clearDisplay();
	display.invertDisplay(false);
#endif
}

void loop() {}