#ifndef NTP_H_
#define NTP_H_

#include <WiFiUdp.h>
#include <NTPClient.h>
#include "debug.h"
#include "oled.h"

#define MAX_NTC_TIME_STR 10

const long utcOffsetInSeconds = -10800; // NTC Offset to update RTC on the internet 

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void initialize_ntp(void);
const char* get_ntp_time(void);

#endif // NTP_H_