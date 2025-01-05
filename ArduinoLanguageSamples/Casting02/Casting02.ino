/*
Investigate how bit shifting is handled and demostrate problem if you use signed instead of unsigned values.

Christopher Lum
lum@uw.edu

Version History
12/31/24: Created
01/01/25: Updated
*/

void setup() {
  //Serial
  Serial.begin(9600);  
}

void loop() {
  /*
  //SCENARIO 1: DEMONSTRATES ERROR
  Serial.println("This produces results that may be unexpected due to padding of 1s");
  int8_t tcByteH = 0b00000001;  //1
  int8_t tcByteM = 0b01011110;  //94
  int8_t tcByteL = 0b11100000;  //-32
  */
  
  //SCENARIO 2: Correct behavior
  uint8_t tcByteH = 0b00000001;  //1
  uint8_t tcByteM = 0b01011110;  //94
  uint8_t tcByteL = 0b11100000;  //224
  
  Serial.print("tcByteH = ");
  Serial.println(tcByteH);
  Serial.println(tcByteH,BIN);
  Serial.println("");

  Serial.print("tcByteM = ");
  Serial.println(tcByteM);
  Serial.println(tcByteM,BIN);
  Serial.println("");

  Serial.print("tcByteL = ");
  Serial.println(tcByteL);
  Serial.println(tcByteL,BIN);
  Serial.println("");

  int32_t ret = tcByteH;
  Serial.println("ret = tcByteH;");
  Serial.print("   ret = ");
  Serial.println(ret);
  Serial.println("");

  ret <<= 8;
  Serial.println("ret <<= 8;");
  Serial.print("   ret = ");
  Serial.println(ret);
  Serial.print("   ret as binary = ");
  Serial.println(ret,BIN);
  Serial.println("");

  ret |= tcByteM;
  Serial.println("ret |= tcByteM;");
  Serial.print("   ret = ");
  Serial.println(ret);
  Serial.print("   ret as binary = ");
  Serial.println(ret,BIN);
  Serial.println("");

  ret <<= 8;
  Serial.println("ret <<= 8;");
  Serial.print("   ret = ");
  Serial.println(ret);
  Serial.print("   ret as binary = ");
  Serial.println(ret,BIN);
  Serial.println("");

  ret |= tcByteL;
  Serial.println("ret |= tcByteL;");
  Serial.print("   ret = ");
  Serial.println(ret);
  Serial.print("   ret as binary = ");
  Serial.println(ret,BIN);
  Serial.println("");

  int32_t temp24 = ret;
  Serial.println("int32_t temp24 = ret;");
  Serial.print("   temp24 = ");
  Serial.println(temp24);
  Serial.print("   temp24 as binary = ");
  Serial.println(ret,BIN);
  Serial.println("");

  Serial.println("-------------------");  
  Serial.println("");
  delay(150000);
}
