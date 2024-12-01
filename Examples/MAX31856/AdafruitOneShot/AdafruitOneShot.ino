// Basic example using one-shot measurement.
// The call to readThermocoupleTemperature() is blocking for O(100ms)

#include <Adafruit_MAX31856.h>

// Use software SPI: CS, DI, DO, CLK
//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
int pin_CS        = 10;
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(pin_CS);

uint8_t sendvalue = 0xFF; //dummy send value used for SPI duplex reading

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("MAX31856 thermocouple test");

  maxthermo.begin();

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

  Serial.print("Thermocouple type: ");
  switch (maxthermo.getThermocoupleType() ) {
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

  Serial.print("MAX31856_TCTYPE_K: ");
  Serial.println(MAX31856_TCTYPE_K);
  Serial.println((uint8_t)MAX31856_TCTYPE_K);
  
  //Get CR0, CR1, CJTO register values
  uint8_t t0 = readRegister8Public(MAX31856_CR0_REG); // get current register value
  Serial.print("MAX31856_CR0_REG: ");
  Serial.println(t0);

  uint8_t t1 = readRegister8Public(MAX31856_CR1_REG); // get current register value
  Serial.print("MAX31856_CR1_REG: ");
  Serial.println(t1);

  uint8_t t2 = readRegister8Public(MAX31856_CJTO_REG); // get current register value
  Serial.print("MAX31856_CJTO_REG: ");
  Serial.println(t2);
  Serial.println("---end setup----");

}

void loop() {
  uint8_t ts = readRegister8Public(MAX31856_CR0_REG);
  Serial.print("loop start MAX31856_CR0_REG (read): ");
  Serial.println(ts);
  
  Serial.print("Cold Junction Temp: ");
  Serial.println(maxthermo.readCJTemperature());

  Serial.print("Thermocouple Temp: ");
  Serial.println(maxthermo.readThermocoupleTemperature());
  // Check and print any faults
  uint8_t fault = maxthermo.readFault();
  if (fault) {
    if (fault & MAX31856_FAULT_CJRANGE) Serial.println("Cold Junction Range Fault");
    if (fault & MAX31856_FAULT_TCRANGE) Serial.println("Thermocouple Range Fault");
    if (fault & MAX31856_FAULT_CJHIGH)  Serial.println("Cold Junction High Fault");
    if (fault & MAX31856_FAULT_CJLOW)   Serial.println("Cold Junction Low Fault");
    if (fault & MAX31856_FAULT_TCHIGH)  Serial.println("Thermocouple High Fault");
    if (fault & MAX31856_FAULT_TCLOW)   Serial.println("Thermocouple Low Fault");
    if (fault & MAX31856_FAULT_OVUV)    Serial.println("Over/Under Voltage Fault");
    if (fault & MAX31856_FAULT_OPEN)    Serial.println("Thermocouple Open Fault");
  }

  uint8_t te = readRegister8Public(MAX31856_CR0_REG);
  Serial.print("loop end MAX31856_CR0_REG (read): ");
  Serial.println(te);

  Serial.println("");
  delay(1000);
}

uint8_t readRegister8Public(uint8_t addr) {
  //write CS low to enable SPI
  digitalWrite(pin_CS,LOW);
  
  uint8_t ret = 0;
  SPI.transfer(addr);
  ret = SPI.transfer(sendvalue);

  //Once transfer is complete, set the CS back to high to stop SPI
  digitalWrite(pin_CS,HIGH);
  
  return ret;
}
