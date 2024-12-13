#ifndef GUARD_LUMSPI_H
#define GUARD_LUMSPI_H

#include <Arduino.h>
#include <SPI.h>

uint8_t readRegister8(SPISettings spiSettings, int pin_CS, uint8_t addr);
void writeRegister8(SPISettings spiSettings, int pin_CS, uint8_t addr, uint8_t data);

#endif
