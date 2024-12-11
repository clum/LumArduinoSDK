/*
Interface with a thermocouple via a MAX31856 chip.

This code uses the SPI library to interact with the sensor.

Christopher Lum
lum@uw.edu

Version History
11/29/24: Created
11/30/24: Continued working
12/01/24: Got CJ temperature reading working
12/11/24: Updated from hex to binary representation for ease of reading
*/

#include <SPI.h>

//CR0
#define MAX31856_CR0_REG_READ     0x00  ///< Config 0 register (read)
#define MAX31856_CR0_REG_WRITE    0x80  ///< Config 0 register (write)

#define MAX31856_CR0_AUTOCONVERT  0b10000000    ///< Config 0 Auto convert flag
#define MAX31856_CR0_1SHOT        0b01000000    ///< Config 0 one shot convert flag
#define MAX31856_CR0_OCFAULT0     0b00010000    ///< Config 0 open circuit fault 0 flag (0001 0000)

//CR1
#define MAX31856_CR1_REG_READ     0x01  ///< Config 1 register (read)
#define MAX31856_CR1_REG_WRITE    0x81  ///< Config 1 register (write)

//MASK (AKA Fault Mask Register)
#define MAX31856_MASK_REG_READ    0x02 ///< Fault Mask register (read)
#define MAX31856_MASK_REG_WRITE   0x82 ///< Fault Mask register (write)

//CJTO
#define MAX31856_CJTO_REG_READ    0x09  ///< Cold-Junction Temperature Offset Register (read)
#define MAX31856_CJTO_REG_WRITE   0x89  ///< Cold-Junction Temperature Offset Register (write)

//CJTL/CJTH
#define MAX31856_CJTH_REG_READ    0x0A  ///< Cold-Junction Temperature Register, MSB (read)
#define MAX31856_CJTL_REG_READ    0x0B  ///< Cold-Junction Temperature Register, LSB (read)

//LTCBH/LTCBM/LTCBL
#define MAX31856_LTCBH_REG_READ   0x0C  ///< Linearized TC Temperature, Byte 2
#define MAX31856_LTCBM_REG_READ   0x0D  ///< Linearized TC Temperature, Byte 1
#define MAX31856_LTCBL_REG_READ   0x0E  ///< Linearized TC Temperature, Byte 0

//Supported thermocouples 
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

//Temperature conversion mode
typedef enum {
  MAX31856_ONESHOT,
  MAX31856_ONESHOT_NOWAIT,
  MAX31856_CONTINUOUS
} max31856_conversion_mode_t;

//SPI
#define SPIMaxSpeed_hz 1000000
SPISettings max31856SpiSettings(SPIMaxSpeed_hz,MSBFIRST,SPI_MODE1);    //MAX31856 uses SPI_MODE1
int pin_CS = 10;    //chip select pin
uint8_t sendvalue = 0xFF; //dummy send value used for SPI duplex reading

//General settings
bool debug = true;

void setup() {
  //Serial
  Serial.begin(115200);

  if(debug) {
    Serial.println("Starting setup");    
  }  

  //SPI
  pinMode(pin_CS,OUTPUT);
  digitalWrite(pin_CS,HIGH);  //disable CS at initialization
  SPI.begin();

  //MAX31856
  SetupMAX31856();  
  
  if(debug) {
    Serial.println("--------------setup-------------");
    displayThermocoupleType();

    uint8_t t0 = readRegister8(MAX31856_CR0_REG_READ); // get current register value
    Serial.print("MAX31856_CR0_REG: ");
    Serial.println(t0);
  
    uint8_t t1 = readRegister8(MAX31856_CR1_REG_READ); // get current register value
    Serial.print("MAX31856_CR1_REG: ");
    Serial.println(t1);
  
    uint8_t t2 = readRegister8(MAX31856_CJTO_REG_READ); // get current register value
    Serial.print("MAX31856_CJTO_REG: ");
    Serial.println(t2);
    
    Serial.println("--------Finished setup-----------");
  }
  
  delay(500);
}

void loop() {
  if(debug) {
    uint8_t ts = readRegister8(MAX31856_CR0_REG_READ);
    Serial.print("MAX31856_CR0_REG_READ at loop start: ");
    Serial.println(ts);
  }
  
  //Read cold junction temperature
  float tempCJ = readColdJunctionTemperature();
  Serial.print("CJ Temp: ");
  Serial.println(tempCJ);

  //Read thermocouple temperature
  float tempTC = readThermocoupleTemperature();
  Serial.print("TC Temp: ");
  Serial.println(tempTC);
  
  if(debug) {
    uint8_t te = readRegister8(MAX31856_CR0_REG_READ);
    Serial.print("MAX31856_CR0_REG_READ at loop end: ");
    Serial.println(te);  
  }

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
  SPI.transfer(addr);
  uint8_t ret = SPI.transfer(sendvalue);
  digitalWrite(pin_CS,HIGH);
  SPI.endTransaction();
  
  return ret;
}

bool SetupMAX31856(void) {
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
Set TC type by writing to the CR1 register.
*/
void setThermocoupleType(max31856_thermocoupletype_t type) {
  uint8_t t = readRegister8(MAX31856_CR1_REG_READ);
  t &= 0xF0; // mask off bottom 4 bits
  t |= (uint8_t)type & 0x0F;
  writeRegister8(MAX31856_CR1_REG_WRITE, t);  
}

void displayThermocoupleType() {
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
}

/*
Read TC type by reading from the CR1 register.
*/
max31856_thermocoupletype_t getThermocoupleType(void) {
  //TC type is stored in bits 0-3 of CR1 register
  uint8_t t = readRegister8(MAX31856_CR1_REG_READ);
  t &= 0x0F;

  return (max31856_thermocoupletype_t)(t);
}

void setAveragingOff() {  
  uint8_t t = readRegister8(MAX31856_CR1_REG_READ);

  //UPDATE LATER SO DIFFERENT AVERAGING SETTINGS BESIDES OFF CAN BE SET
  uint8_t averagingType = 0x00;
    
  t &= 0x0F; // mask off top 4 bits
  t |= averagingType & 0xF0;

  writeRegister8(MAX31856_CR1_REG_WRITE, t);  
}

/*
Set conversion mode by writing to the CR0 register.
*/
void setConversionMode(max31856_conversion_mode_t mode) {
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

/*
Read the cold junction temperature by reading from the CJTH and CJTL registers
and performing appropriate bitshifting.
*/
float readColdJunctionTemperature() {
  uint8_t dataCJTH = readRegister8(MAX31856_CJTH_REG_READ);
  uint8_t dataCJTL = readRegister8(MAX31856_CJTL_REG_READ);
  
  uint16_t ret = dataCJTH;
  
  ret <<= 8;
  ret |= dataCJTL;

  float tempCJ = ret/256.0;

  return tempCJ;
}

/*
Read the thermocouple temperature by reading from the LTCBH, LTCBM, and LTCBL registers
and performing appropriate bitshifting.
*/
float readThermocoupleTemperature() {
  //for one-shot make it happen
  triggerOneShot();
  uint32_t start = millis();
  while (!conversionComplete()) {
    if (millis() - start > 250)
      return NAN;
    delay(10);
  }

  //read the thermocouple temperature registers (3 bytes)
  uint8_t tcByte2 = readRegister8(MAX31856_LTCBH_REG_READ);
  uint8_t tcByte1 = readRegister8(MAX31856_LTCBM_REG_READ);
  uint8_t tcByte0 = readRegister8(MAX31856_LTCBL_REG_READ);
  
  int32_t ret = tcByte2;
  ret <<= 8;
  ret |= tcByte1;
  ret <<= 8;
  ret |= tcByte0;

  int32_t temp24 = ret;

  // and compute temperature
  if (temp24 & 0x800000) {
    temp24 |= 0xFF000000; // fix sign
  }

  temp24 >>= 5; // bottom 5 bits are unused

  return temp24 * 0.0078125;    
}

/*
Turn off autoconvert and turn on one-shot mode by writing appropriate bits to the CR0 register.
*/
void triggerOneShot() {
  uint8_t t = readRegister8(MAX31856_CR0_REG_READ); // get current register value

  if(debug) {
    Serial.print("MAX31856_CR0_REG_READ at triggerOneShot start: ");
    Serial.println(t);
  }
  
  t &= ~MAX31856_CR0_AUTOCONVERT;             // turn off autoconvert
  t |= MAX31856_CR0_1SHOT;                    // turn on one-shot
  writeRegister8(MAX31856_CR0_REG_WRITE,t);   // write value back to register

  if(debug) {
    uint8_t te = readRegister8(MAX31856_CR0_REG_READ);
    Serial.print("MAX31856_CR0_REG_READ at triggerOneShot end: ");
    Serial.println(te);
  }
    
  //conversion starts when CS goes high
}

/*
Determine if the temperature conversion is complete.
*/
bool conversionComplete(void) {
  return !(readRegister8(MAX31856_CR0_REG_READ) & MAX31856_CR0_1SHOT);
}
