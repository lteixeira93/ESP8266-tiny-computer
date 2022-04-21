#ifndef _RTC_H_
#define _RTC_H_

#include <Wire.h>
#include <SPI.h>
#include <RtcDS3231.h>
#include "debug.h"

#define MAX_RTC_TIME_STR 20

RtcDS3231<TwoWire> rtc(Wire);

void initialize_rtc(void);
void show_timestamp(void);
void update_rtc_ntp(void);

#endif // _RTC_H_