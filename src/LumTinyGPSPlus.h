#ifndef GUARD_LUMTINYGPSPLUS_H
#define GUARD_LUMTINYGPSPLUS_H

#include <Arduino.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

void DelayAndEncodeGPSViaSoftwareSerial(unsigned long ms, TinyGPSPlus* gps, SoftwareSerial* ss);

#endif
