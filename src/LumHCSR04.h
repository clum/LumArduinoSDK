#ifndef GUARD_LUMHCSR04_H
#define GUARD_LUMHCSR04_H

#include <Arduino.h>

int HCSR04GetTimeOfFlight_ms(int PinHCS04Trigger, int PinHCS04Echo, unsigned long timeout = 100000);
int HCSR04GetDistance_cm(int PinHCS04Trigger, int PinHCS04Echo, unsigned long timeout = 100000);

#endif
