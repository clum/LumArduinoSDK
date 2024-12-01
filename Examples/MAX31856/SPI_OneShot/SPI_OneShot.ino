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
#define MAX31856_CR0_OCFAULT0     0x10  ///< Config 0 open circuit fault 0 flag (0001 0000)

#define MAX31856_CR1_REG_READ     0x01  ///< Config 1 register (read)
#define MAX31856_CR1_REG_WRITE    0x81  ///< Config 1 register (write)

#define MAX31856_MASK_REG_READ    0x02 ///< Fault Mask register (read)
#define MAX31856_MASK_REG_WRITE   0x82 ///< Fault Mask register (write)

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

/** Temperature conversion mode */
typedef enum {
  MAX31856_ONESHOT,
  MAX31856_ONESHOT_NOWAIT,
  MAX31856_CONTINUOUS
} max31856_conversion_mode_t;

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
  
  begin();  

  Serial.print("Thermocouple type: ");
  switch (getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }

  //Get CR0 and CR1 register values
  uint8_t t0 = readRegister8(MAX31856_CR0_REG_READ); // get current register value
  Serial.print("MAX31856_CR0_REG: ");
  Serial.println(t0);

  uint8_t t1 = readRegister8(MAX31856_CR1_REG_READ); // get current register value
  Serial.print("MAX31856_CR1_REG: ");
  Serial.println(t1);

  uint8_t t2 = readRegister8(MAX31856_CJTO_REG_READ); // get current register value
  Serial.print("MAX31856_CJTO_REG: ");
  Serial.println(t2);
  
  Serial.println("Finished setup");
  delay(500);
}

void loop() {
  uint8_t ts = readRegister8(MAX31856_CR0_REG_READ);
  Serial.print("loop start MAX31856_CR0_REG_READ: ");
  Serial.println(ts);
  
  //--------------SPI START----------------------
  SPI.beginTransaction(max31856SpiSettings);
    
  //write CS low to enable SPI
  digitalWrite(pin_CS,LOW);

  
  //select which register to read by sending a single byte with the address of the desired register
  SPI.transfer(MAX31856_CJTH_REG_READ);
  uint8_t dataCJTH = SPI.transfer(sendvalue);
  
  //SPI.transfer(MAX31856_CJTL_REG_READ);
  uint8_t dataCJTL = SPI.transfer(sendvalue);
  
  
  //uint8_t dataCJTH = 0;
  //uint8_t dataCJTL = 0;  

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
  
  ret <<= 8;
  ret |= dataCJTL;

  float tempCJ = ret/256.0;

  //-------------------------------------------
  Serial.print("Cold Junction Temp: ");
  //Serial.println(dataCJTH);
  //Serial.println(dataCJTL);
  //Serial.println(ret);
  Serial.println(tempCJ);

  uint8_t te = readRegister8(MAX31856_CR0_REG_READ);
  Serial.print("loop end MAX31856_CR0_REG_READ: ");
  Serial.println(te);
  
  Serial.println("");  
  delay(1000);
}

void writeRegister8(uint8_t addr, uint8_t data) {
  SPI.beginTransaction(max31856SpiSettings);
  digitalWrite(pin_CS,LOW);
  SPI.transfer(addr);
  SPI.transfer(data);
  digitalWrite(pin_CS,HIGH);
  SPI.endTransaction();
}

uint8_t readRegister8(uint8_t addr) {
  SPI.beginTransaction(max31856SpiSettings);
  digitalWrite(pin_CS,LOW);
  
  uint8_t ret = 0;
  SPI.transfer(addr);
  ret = SPI.transfer(sendvalue);
  digitalWrite(pin_CS,HIGH);
  SPI.endTransaction();
  
  return ret;
}

bool begin(void) {
  /*
  initialized = spi_dev.begin();

  if (!initialized)
    return false;
  */
  // assert on any fault
  writeRegister8(MAX31856_MASK_REG_WRITE, 0x0);

  // enable open circuit fault detection
  writeRegister8(MAX31856_CR0_REG_WRITE, MAX31856_CR0_OCFAULT0);

  // set cold junction temperature offset to zero
  writeRegister8(MAX31856_CJTO_REG_WRITE, 0x0);

  // set Type K by default
  setThermocoupleType(MAX31856_TCTYPE_K);

  // set averaging off
  setAveragingOff();
  
  // set One-Shot conversion mode
  setConversionMode(MAX31856_ONESHOT);

  return true;
}

/*
Set TC type by writing to CR1 register.
*/
void setThermocoupleType(max31856_thermocoupletype_t type) {
  Serial.println("setThermocoupleType");
  
  uint8_t t = readRegister8(MAX31856_CR1_REG_READ);
  Serial.println("t after readRegister8");
  Serial.println(t);
  
  t &= 0xF0; // mask off bottom 4 bits
  t |= (uint8_t)type & 0x0F;

  Serial.println("t after bitwise operations");
  Serial.println(t);
  writeRegister8(MAX31856_CR1_REG_WRITE, t);  
}

void setAveragingOff() {  
  Serial.println("setAveragingOff");
  
  uint8_t t = readRegister8(MAX31856_CR1_REG_READ);
  Serial.println("t after readRegister8");
  Serial.println(t);

  //UPDATE LATER SO DIFFERENT AVERAGING SETTINGS BESIDES OFF CAN BE SET
  uint8_t averagingType = 0x00;
    
  t &= 0x0F; // mask off top 4 bits
  t |= averagingType & 0xF0;

  Serial.println("t after bitwise operations");
  Serial.println(t);
  writeRegister8(MAX31856_CR1_REG_WRITE, t);  
}

max31856_thermocoupletype_t getThermocoupleType(void) {
  uint8_t t = readRegister8(MAX31856_CR1_REG_READ);
  t &= 0x0F;

  return (max31856_thermocoupletype_t)(t);
}

void setConversionMode(max31856_conversion_mode_t mode) {
  //conversionMode = mode;
  max31856_conversion_mode_t conversionMode  = mode;
  uint8_t t = readRegister8(MAX31856_CR0_REG_READ); // get current register value
  if (conversionMode == MAX31856_CONTINUOUS) {
    t |= MAX31856_CR0_AUTOCONVERT; // turn on automatic
    t &= ~MAX31856_CR0_1SHOT;      // turn off one-shot
  } else {
    t &= ~MAX31856_CR0_AUTOCONVERT; // turn off automatic
    t |= MAX31856_CR0_1SHOT;        // turn on one-shot
  }
  writeRegister8(MAX31856_CR0_REG_WRITE, t); // write value back to register
}

void triggerOneShot(void) {
  //uint8_t t = readRegister8(MAX31856_CR0_REG); // get current register value

  SPI.transfer(MAX31856_CR0_REG_READ);
  uint8_t t = SPI.transfer(sendvalue);
  Serial.print("MAX31856_CR0_REG_READ inside triggerOneShot: ");
  Serial.println(t);
  
  //Serial.print("triggerOneShot MAX31856_CR0_REG_READ: ");
  //Serial.println(t);
  
  t &= ~MAX31856_CR0_AUTOCONVERT;              // turn off autoconvert
  t |= MAX31856_CR0_1SHOT;                     // turn on one-shot

  Serial.print("t after bit operations: ");
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
