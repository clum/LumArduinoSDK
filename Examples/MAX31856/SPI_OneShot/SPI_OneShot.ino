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
12/14/24: Updated documentation (while working to port to MATLAB)
12/18/24: Minor update to documentation
*/

#include <SPI.h>
#include <LumMisc.h>
#include"LumSPI.h"

//CR0
#define MAX31856_CR0_REG_READ     0x00          //Config 0 register (read)
#define MAX31856_CR0_REG_WRITE    0x80          //Config 0 register (write)

//CR1
#define MAX31856_CR1_REG_READ     0x01          //Config 1 register (read)
#define MAX31856_CR1_REG_WRITE    0x81          //Config 1 register (write)

//MASK (AKA Fault Mask Register)
#define MAX31856_MASK_REG_READ    0x02          //Fault Mask register (read)
#define MAX31856_MASK_REG_WRITE   0x82          //Fault Mask register (write)

//CJTO
#define MAX31856_CJTO_REG_READ    0x09          //Cold-Junction Temperature Offset Register (read)
#define MAX31856_CJTO_REG_WRITE   0x89          //Cold-Junction Temperature Offset Register (write)

//CJTL/CJTH
#define MAX31856_CJTH_REG_READ    0x0A          //Cold-Junction Temperature Register, MSB (read)
#define MAX31856_CJTL_REG_READ    0x0B          //Cold-Junction Temperature Register, LSB (read)

//LTCBH/LTCBM/LTCBL
#define MAX31856_LTCBH_REG_READ   0x0C          //Linearized TC Temperature, Byte 2
#define MAX31856_LTCBM_REG_READ   0x0D          //Linearized TC Temperature, Byte 1
#define MAX31856_LTCBL_REG_READ   0x0E          //Linearized TC Temperature, Byte 0

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
  MAX31856_CONVERSIONMODE_ONESHOT,
  MAX31856_CONVERSIONMODE_ONESHOTNOWAIT,
  MAX31856_CONVERSIONMODE_CONTINUOUS
} max31856_conversionmode_t;

//Averaging mode
typedef enum {
  MAX31856_AVERAGINGMODE_1SAMPLES,
  MAX31856_AVERAGINGMODE_2SAMPLES,
  MAX31856_AVERAGINGMODE_4SAMPLES,
  MAX31856_AVERAGINGMODE_8SAMPLES,
  MAX31856_AVERAGINGMODE_16SAMPLES
} max31856_averagingmode_t;

//Open-circuit detection mode
typedef enum {
  MAX31856_OCDETECTIONMODE_DISABLED,
  MAX31856_OCDETECTIONMODE_ENABLEDA,
  MAX31856_OCDETECTIONMODE_ENABLEDB,
  MAX31856_OCDETECTIONMODE_ENABLEDC
} max31856_opencircuitdetectionmode_t;

//SPI
#define SPIMaxSpeed_hz 1000000
SPISettings max31856SpiSettings(SPIMaxSpeed_hz,MSBFIRST,SPI_MODE1);    //MAX31856 uses SPI_MODE1
int pin_CS = 10;                                                      //chip select pin
uint8_t sendvalue = 0xFF;                                             //dummy send value used for SPI duplex reading

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

    uint8_t t0 = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ); // get current register value
    Serial.print("MAX31856_CR0_REG: ");
    Serial.println(t0);
  
    uint8_t t1 = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_READ); // get current register value
    Serial.print("MAX31856_CR1_REG: ");
    Serial.println(t1);
  
    uint8_t t2 = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CJTO_REG_READ); // get current register value
    Serial.print("MAX31856_CJTO_REG: ");
    Serial.println(t2);
    
    Serial.println("--------Finished setup-----------");
  }
  
  delay(500);
}

void loop() {
  if(debug) {
    uint8_t ts = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ);
    Serial.print("MAX31856_CR0_REG_READ at loop start: ");
    Serial.println(ts);
  }

  //trigger a one-shot conversion
  triggerOneShot();
  uint32_t start = millis();
  while (!conversionComplete()) {
    if (millis() - start > 250)
      return NAN;
    delay(10);
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
    uint8_t te = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ);
    Serial.print("MAX31856_CR0_REG_READ at loop end: ");
    Serial.println(te);  
  }

  Serial.println("");
  delay(1000);
}

/*
Setup and initialize various registers on the MAX31856
*/
bool SetupMAX31856(void) {
  //----------Setup MASK register------------
  //assert on any fault (set all bits to 0)
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_MASK_REG_WRITE, 0x0);

  //----------Setup CR0 register-------------
  //initialize register to all 0.  As a byproduct, this sets the following:
  //  (bit 7)   CMODE = normally off mode
  //  (bit 6)   1SHOT = no conversions requested
  //  (bit 5:4) OCFAULT = disabled
  //  (bit 3)   CJ = cold-junction temperature sensor enabled
  //  (bit 2)   FAULT = comparator mode
  //  (bit 1)   FAULTCLR = default
  //  (bit 0)   50/60 Hz = 60 Hz
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_WRITE, 0x0);

  //enable open circuit fault detection
  setOpenCircuitDetectionMode(MAX31856_OCDETECTIONMODE_ENABLEDA);

  //set One-Shot conversion mode
  setConversionMode(MAX31856_CONVERSIONMODE_ONESHOT);
   
  //----------Setup CR1 register-------------
  //initialize register to all 0.  As a byproduct, this sets the following:
  //  (bit 7)   <RESERVED>
  //  (bit 6:4) AVGSEL = 1 sample
  //  (bit 3:0) TC TYPE = B Type
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_WRITE, 0x0);

  //set thermocouple type
  setThermocoupleType(MAX31856_TCTYPE_K);

  //set averaging mode
  setAveragingMode(MAX31856_AVERAGINGMODE_1SAMPLES);

  //----------Setup CJTO register-------------
  //set cold junction temperature offset to zero (set all bits to 0)
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CJTO_REG_WRITE, 0x0);
  
  return true;
}

//-----------------------CR0 Functions-------------------------------
/*
Set conversion mode by writing to the CR0 register (bit 7 for CMODE, bit 6 for 1SHOT).
*/
void setConversionMode(max31856_conversionmode_t mode) {
  //get current register value
  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ);

  switch(mode) {
    case MAX31856_CONVERSIONMODE_ONESHOT:
    {
      t = BitSetToValue(t,7,0); //turn off automatic
      t = BitSetToValue(t,6,1); //turn on one-shot
      break;
    }
    case MAX31856_CONVERSIONMODE_ONESHOTNOWAIT:
    {
      Serial.println("Unsupported max31856_conversionmode_t mode");
      break;
    }
    case MAX31856_CONVERSIONMODE_CONTINUOUS:
    {
      t = BitSetToValue(t,7,1); //turn on automatic
      t = BitSetToValue(t,6,0); //turn off one-shot
      break;
    }
    default:
    {
      Serial.println("Unsupported max31856_conversionmode_t mode");
      break;
    }
  }

  //write value back to register
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_WRITE, t);
}

/*
Set open circuit detection mode by writing to the CR0 register (bit 5:4 for OCFAULT).

AKA Table 4 in MAX31856 data sheet
*/
void setOpenCircuitDetectionMode(max31856_opencircuitdetectionmode_t mode) {
  //get current register value
  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ);
  
  switch(mode) {
    case MAX31856_OCDETECTIONMODE_DISABLED:
    {
      t = BitSetToValue(t,5,0);
      t = BitSetToValue(t,4,0);
      break;
    }
    case MAX31856_OCDETECTIONMODE_ENABLEDA:
    {
      t = BitSetToValue(t,5,0);
      t = BitSetToValue(t,4,1);      
      break;
    }
    case MAX31856_OCDETECTIONMODE_ENABLEDB:
    {
      t = BitSetToValue(t,5,1);
      t = BitSetToValue(t,4,0);      
      break;
    }
    case MAX31856_OCDETECTIONMODE_ENABLEDC:
    {
      t = BitSetToValue(t,5,1);
      t = BitSetToValue(t,4,1);      
      break;
    }
    default:
    {
      Serial.println("Unsupported max31856_opencircuitdetectionmode_t mode");
      break;
    }
  }

  //write value back to register
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_WRITE, t);
}

/*
Turn off autoconvert and turn on one-shot mode by writing appropriate bits to the CR0 register.
*/
void triggerOneShot() {
  //Version History
  //12/11/24: Created
  //12/18/24: Updated how autoconvert and one-shot are turned off and on
  
  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ); // get current register value

  if(debug) {
    Serial.print("MAX31856_CR0_REG_READ at triggerOneShot start: ");
    Serial.println(t);
  }

  t = BitSetToValue(t,7,0);   //turn off autoconvert
  t = BitSetToValue(t,6,1);   //turn on one-shot
    
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_WRITE,t);   // write value back to register

  if(debug) {
    uint8_t te = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ);
    Serial.print("MAX31856_CR0_REG_READ at triggerOneShot end: ");
    Serial.println(te);
  }
    
  //conversion starts when CS goes high
}

/*
Determine if the temperature conversion is complete.
*/
bool conversionComplete(void) {
  //Version History
  //12/12/24: Created
  //12/18/24: Changed implementation to simply check bit 6.  Original functionalty was "return !(readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ) & MAX31856_CR0_1SHOT);"

  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR0_REG_READ);
  if(BitIs1(t,6)) {
    return false;
  } else {
    return true;
  }
}

//-----------------------CR1 Functions-------------------------------
/*
Set TC type by writing to the CR1 register.
*/
void setThermocoupleType(max31856_thermocoupletype_t tcType) {
  //Version History
  //12/18/24: Updating documentation

  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_READ);  // get current register value
  t &= 0xF0; // mask off bottom 4 bits
  t |= (uint8_t)tcType & 0x0F;
  
  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_WRITE, t);  
}

/*
Read TC type by reading from the CR1 register.
*/
max31856_thermocoupletype_t getThermocoupleType(void) {
  //Version History
  //12/18/24: Minor update to documentation
  
  //TC type is stored in bits 0-3 of CR1 register
  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_READ);
  t &= 0x0F;

  return (max31856_thermocoupletype_t)(t);
}

/*
Display the TC type to the serial monitor 
*/
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
Set averaging by writing to the CR1 register (bits 4,5,6)
*/
void setAveragingMode(max31856_averagingmode_t averagingMode) {  
  uint8_t t = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_READ);

  //set bits 7,6,5,4 (although bit 7 is not used as it is reserved)
  switch (averagingMode) {
    case MAX31856_AVERAGINGMODE_1SAMPLES:
    {
      //000 = 1 sample
      t = BitSetToValue(t,6,0);
      t = BitSetToValue(t,5,0);
      t = BitSetToValue(t,4,0);
      break;
    }

    case MAX31856_AVERAGINGMODE_2SAMPLES:
    {
      //001 = 2 sample
      t = BitSetToValue(t,6,0);
      t = BitSetToValue(t,5,0);
      t = BitSetToValue(t,4,1);
      break;
    }

    case MAX31856_AVERAGINGMODE_4SAMPLES:
    {
      //010 = 4 sample
      t = BitSetToValue(t,6,0);
      t = BitSetToValue(t,5,1);
      t = BitSetToValue(t,4,0);
      break;
    }

    case MAX31856_AVERAGINGMODE_8SAMPLES:
    {
      //011 = 8 sample
      t = BitSetToValue(t,6,0);
      t = BitSetToValue(t,5,1);
      t = BitSetToValue(t,4,1);
      break;
    }

    case MAX31856_AVERAGINGMODE_16SAMPLES:
    {
      //1xx = 16 sample
      t = BitSetToValue(t,6,1);
      t = BitSetToValue(t,5,1);
      t = BitSetToValue(t,4,1);
      break;
    }

    default:
    {
      Serial.println("Unsupported averagingMode mode");
      break;
    }
  }

  writeRegister8(max31856SpiSettings,pin_CS,MAX31856_CR1_REG_WRITE, t);  
}

//-----------------------CJTH/CJTL Functions-------------------------------
/*
Read the cold junction temperature by reading from the CJTH and CJTL registers
and performing appropriate bitshifting/conversions.
*/
float readColdJunctionTemperature() {
  //Version History
  //12/18/24: Minor update to documentation
  
  uint8_t dataCJTH = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CJTH_REG_READ);
  uint8_t dataCJTL = readRegister8(max31856SpiSettings,pin_CS,MAX31856_CJTL_REG_READ);
  
  uint16_t ret = dataCJTH;
  
  ret <<= 8;
  ret |= dataCJTL;

  float tempCJ = ret/256.0;

  return tempCJ;
}

//-----------------------LTCBH/LTCBM/LTCBL Functions-------------------------------
/*
Read the thermocouple temperature by reading from the LTCBH, LTCBM, and LTCBL registers
and performing appropriate bitshifting/conversions.
*/
float readThermocoupleTemperature() {
  //Version History
  //12/18/24: Moved triggerOneShot to loop
  
  //read the thermocouple temperature registers (3 bytes)
  uint8_t tcByte2 = readRegister8(max31856SpiSettings,pin_CS,MAX31856_LTCBH_REG_READ);
  uint8_t tcByte1 = readRegister8(max31856SpiSettings,pin_CS,MAX31856_LTCBM_REG_READ);
  uint8_t tcByte0 = readRegister8(max31856SpiSettings,pin_CS,MAX31856_LTCBL_REG_READ);
  
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
