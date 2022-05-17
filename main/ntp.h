#ifndef _NTP_H_
#define _NTP_H_

#include <WiFiUdp.h>
#include <NTPClient.h>
#include "debug.h"
#include "oled.h"

#define MAX_NTC_TIME_STR 15

void initialize_ntp(void);
const char* get_ntp_time(void);

#endif // _NTP_H_