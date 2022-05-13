
# ESP8266-tiny-computer

**This works with the ESP8266 Arduino platform**

[https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)

**This works with the ESP32 Arduino platform** 

[https://github.com/espressif/arduino-esp32](https://github.com/espressif/arduino-esp32)

-------
## How It Works
- This project explore almost all of the features of NodeMCU - ESP8266 platform, this way becoming a tiny computer
- After code is loaded, NodeMCU will initialize all peripherals (I2C and SPI)
- NodeMCU will try to connect to a previous saved network, if not successfull it will enable an access point with name ESP_AP so you can connect and scan networks through a graphical mode
- After successfully connected to a network it will update RTC clock using NTP over the internet and after  this, connect to mqtt broker (Adafruit IO) to send sensor data to a cloud dashboard
- Everyday at a specific time, using RTC, NodeMCU will send DHT11 sensor data (Humidity and Temperature to the cloud and also save data locally in SD card in .csv format)
- For each step, it will show informations on OLED display

## How It Looks
Please see \resources\images

## Wishlist
- [x] More info on OLED display
- [x] Improve consistency
- [x] Add secure coding techniques
- [x] Perform longterm and reliability testing

## Quick Start

### Installing
Install libs from resources\requirements\requirements.txt in Arduino library manager and enable ESP8266 support on Arduino IDE

### Debug
Change debug level in debug.h setting or unsetting those flags:
* DEBUG_ESP
* DEBUG_OLED
* DEBUG_MQTT
* DEBUG_RTC
* DEBUG_SD
* DEBUG_DHT
* DEBUG_NTP
* DEBUG_WEBSERVER
* DEBUG_IP

#### References

* https://github.com/tzapu/WiFiManager
* https://create.arduino.cc/projecthub/najad/interfacing-and-displaying-images-on-oled-59344a
* https://thekurks.net/blog/2018/3/20/nodemcu-data-logger
* https://github.com/esp8266

#### Inspiration
 * TCG (love)