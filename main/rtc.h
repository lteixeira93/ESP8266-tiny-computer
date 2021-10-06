#ifndef RTC_H_
#define RTC_H_

#include <Wire.h>
#include <SPI.h>
#include <RtcDS3231.h>
#include "debug.h"

RtcDS3231<TwoWire> rtc(Wire);

void initialize_rtc(void);
void show_timestamp(void);

#endif // RTC_H_