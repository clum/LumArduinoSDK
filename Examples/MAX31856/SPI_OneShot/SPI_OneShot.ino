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

#define MAX31856_CR0_REG_READ     0x00  ///< Config 0 register (read)
#define MAX31856_CR0_REG_WRITE    0x80  ///< Config 0 register (write)

#define MAX31856_CR0_AUTOCONVERT  0x80  ///< Config 0 Auto convert flag
#define MAX31856_CR0_1SHOT        0x40  ///< Config 0 one shot convert flag

#define MAX31856_CJTO_REG_READ    0x09  ///< Cold-Junction Temperature Offset Register (read)
#define MAX31856_CJTO_REG_WRITE   0x89  ///< Cold-Junction Temperature Offset Register (write)

#define MAX31856_CJTH_REG_READ    0x0A  ///< Cold-Junction Temperature Register, MSB (read)
#define MAX31856_CJTL_REG_READ    0x0B  ///< Cold-Junction Temperature Register, LSB (read)

/** Multiple types of thermocouples supported */
typedef enum {
  MAX31856_TCTYPE_B = 0b0000,
  MAX31856_TCTYPE_E = 0b0001,
  MAX31856_TCTYPE_J = 0b0010,
  MAX31856_TCTYPE_K = 0b0011,
  MAX31856_TCTYPE_N = 0b0100,
  MAX31856_TCTYPE_R = 0b0101,
  MAX31856_TCTYPE_S = 0b0110,
  MAX31856_TCTYPE_T = 0b0111,
  MAX31856_VMODE_G8 = 0b1000,
  MAX31856_VMODE_G32 = 0b1100,
} max31856_thermocoupletype_t;

//Constants
int pin_CS        = 10;
int pin_SDI_MOSI  = 11;
int pin_SDO_MISO  = 12;

SPISettings max31856SpiSettings(1000000,MSBFIRST,SPI_MODE1);    //MAX31856 uses SPI_MODE1
uint8_t sendvalue = 0xFF; //dummy send value used for SPI duplex reading

void setup() {
  //Serial
  Serial.begin(115200);
  Serial.println("Starting setup");

  //SPI
  pinMode(pin_CS,OUTPUT);
  digitalWrite(pin_CS,HIGH);  //disable CS at initialization
  
  SPI.begin();
  Serial.println("Finished setup");
  delay(500);
}

void loop() {

  //--------------SPI START----------------------
  SPI.beginTransaction(max31856SpiSettings);
  
  //write CS low to enable SPI
  digitalWrite(pin_CS,LOW);
  
  //select which register to read by sending a single byte with the address of the desired register
  SPI.transfer(MAX31856_CJTH_REG_READ);
  uint8_t dataCJTH = SPI.transfer(sendvalue);

  SPI.transfer(MAX31856_CJTL_REG_READ);
  uint8_t dataCJTL = SPI.transfer(sendvalue);

  //setup for another one-shot conversion of temperature
  triggerOneShot();

  //setup autoconvert of temperature
  //triggerAutoConvert();
  
  //Once transfer is complete, set the CS back to high to stop SPI
  digitalWrite(pin_CS,HIGH);

  SPI.endTransaction();
  //--------------SPI END------------------------

  //Bit shift and conversion
  uint16_t ret = dataCJTH;
  uint16_t retBefore = ret;
  
  ret <<= 8;
  ret |= dataCJTL;

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

void writeRegister8(uint8_t addr, uint8_t data) {
  SPI.transfer(addr);
  SPI.transfer(data);
}

bool begin(void) {
  /*
  initialized = spi_dev.begin();

  if (!initialized)
    return false;

  // assert on any fault
  writeRegister8(MAX31856_MASK_REG, 0x0);

  // enable open circuit fault detection
  writeRegister8(MAX31856_CR0_REG, MAX31856_CR0_OCFAULT0);
  */

  // set cold junction temperature offset to zero
  writeRegister8(MAX31856_CJTO_REG_WRITE, 0x0);

  // set Type K by default
  //setThermocoupleType(MAX31856_TCTYPE_K);

  // set One-Shot conversion mode
  //setConversionMode(MAX31856_ONESHOT);
}

void triggerOneShot(void) {
  //uint8_t t = readRegister8(MAX31856_CR0_REG); // get current register value

  SPI.transfer(MAX31856_CR0_REG_READ);
  uint8_t t = SPI.transfer(sendvalue);

  Serial.print("MAX31856_CR0_REG_READ: ");
  Serial.println(t);
  
  t &= ~MAX31856_CR0_AUTOCONVERT;              // turn off autoconvert
  t |= MAX31856_CR0_1SHOT;                     // turn on one-shot

  Serial.println(t);
  
  //writeRegister8(MAX31856_CR0_REG, t);         // write value back to register
  SPI.transfer(MAX31856_CR0_REG_WRITE);
  SPI.transfer(t);

  delay(200);
}

void triggerAutoConvert(void) {
  //uint8_t t = readRegister8(MAX31856_CR0_REG); // get current register value

  SPI.transfer(MAX31856_CR0_REG_READ);
  uint8_t t = SPI.transfer(sendvalue);

  Serial.print("MAX31856_CR0_REG_READ: ");
  Serial.println(t);
  
  t |= MAX31856_CR0_AUTOCONVERT;              // turn on autoconvert
  
  Serial.println(t);
  
  //writeRegister8(MAX31856_CR0_REG, t);         // write value back to register
  SPI.transfer(MAX31856_CR0_REG_WRITE);
  SPI.transfer(t);
}