#include "LumSPI.h"
#include <Arduino.h>
#include <SPI.h>

uint8_t readRegister8(SPISettings spiSettings, int pin_CS, uint8_t addr) {
	uint8_t sendvalue = 0xFF; //dummy send value used for SPI duplex reading

	SPI.beginTransaction(spiSettings);
	digitalWrite(pin_CS, LOW);
	SPI.transfer(addr);
	uint8_t ret = SPI.transfer(sendvalue);
	digitalWrite(pin_CS, HIGH);
	SPI.endTransaction();

	return ret;
}

void writeRegister8(SPISettings spiSettings, int pin_CS, uint8_t addr, uint8_t data) {
	SPI.beginTransaction(spiSettings);
	digitalWrite(pin_CS, LOW);
	SPI.transfer(addr);
	SPI.transfer(data);
	digitalWrite(pin_CS, HIGH);
	SPI.endTransaction();
}
