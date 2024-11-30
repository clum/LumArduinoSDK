/*
Interface with a thermocouple via a MAX31856 chip.

This code uses the SPI library to interact with the sensor.

Christopher Lum
lum@uw.edu

Version History
11/29/24: Created
11/30/24: Continued working
*/

#include <SPI.h>

#define MAX31856_CJTH_REG 0x0A  ///< Cold-Junction Temperature Register, MSB
#define MAX31856_CJTL_REG 0x0B  ///< Cold-Junction Temperature Register, LSB

//Constants
int pin_CS        = 10;
int pin_SDI_MOSI  = 11;
int pin_SDO_MISO  = 12;

SPISettings max31856SpiSettings(1000000,MSBFIRST,SPI_MODE1);

void setup() {
  //Serial
  Serial.begin(115200);
  Serial.println("Starting setup");

  //SPI
  pinMode(pin_CS,OUTPUT);
  digitalWrite(pin_CS,HIGH);  //disable CS at initialization
  
  //pinMode(pin_SDI_MOSI,OUTPUT);
  //pinMode(pin_SDO_MISO,INPUT);
  
  SPI.begin();
  Serial.println("Finished setup");
  delay(500);
}

void loop() {

  //--------------SPI START----------------------
  //uint8_t sendvalue = 0x00;  
  uint8_t sendvalue = 0xFF;

  SPI.beginTransaction(max31856SpiSettings);
  
  //write CS low to enable SPI
  digitalWrite(pin_CS,LOW);
  
  //select which register to read by sending a single byte with the address of the desired register
  SPI.transfer(MAX31856_CJTH_REG);
  uint8_t dataCJTH = SPI.transfer(sendvalue);

  SPI.transfer(MAX31856_CJTL_REG);
  uint8_t dataCJTL = SPI.transfer(sendvalue);
  
  //Once transfer is complete, set the CS back to high to stop SPI
  digitalWrite(pin_CS,HIGH);

  SPI.endTransaction();
  //--------------SPI END------------------------

  //Bit shift and conversion
  uint16_t ret = dataCJTH;
  uint16_t retBefore = ret;
  
  ret <<= 8;
  ret |= MAX31856_CJTL_REG;

  float tempCJ = ret/256.0;

  //-------------------------------------------
  Serial.println("Cold Junction Temp: ");
  Serial.println(dataCJTH);
  Serial.println(dataCJTL);
  //Serial.println(retBefore);
  //Serial.println(ret);
  Serial.println(tempCJ);
  Serial.println("");
  
  delay(1000);
}
