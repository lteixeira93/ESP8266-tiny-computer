
# ESP8266-tiny-computer

**This works with the ESP8266 Arduino platform**

[https://github.com/esp8266/Arduino](https://github.com/esp8266/Arduino)

-------
## How it Works
- This project aims to use most of NodeMCU features - ESP8266 platform, this way becoming a tiny computer
- After code is loaded, NodeMCU will initialize (I2C, SPI, Webserver and MQTT)
- NodeMCU will try to connect to a previous saved network, if not successfull it will enable an access point so you can connect and scan networks through a graphical interface
- After successfully connected to a network it will update RTC clock using NTP server over the internet and then connect to mqtt broker (Adafruit IO) to send DHT11 sensor data to a cloud dashboard
- Using RTC and specified time, NodeMCU will send DHT11 sensor data (Humidity and Temperature to the cloud and also save data locally on SD card in .csv format)
- For each step, it will show informations on OLED display and serial monitor

## Quick Start

### Installing
Install libs from resources\requirements\requirements.txt on Arduino library manager and enable ESP8266 board support on Arduino IDE

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