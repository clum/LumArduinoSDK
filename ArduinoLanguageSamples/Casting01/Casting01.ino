/*
Investigate how casting between unsigned and signed data types is handled.

Christopher Lum
lum@uw.edu

Version History
12/30/24: Created
12/31/24: Updated
*/

void setup() {
  //Serial
  Serial.begin(9600);  
}

void loop() {
  //Note
  //  Bit Pattern   uint8   int8
  //  0b11001100    204     -53
  
  //start with an unsigned int
  uint8_t x_uint8_t = 0b11001100;   //204
  
  Serial.print("x_uint8_t = ");
  Serial.println(x_uint8_t);
  Serial.println("");
  
  Serial.println("cast x_uint8_t to signed int");
  int8_t x_int8_t = (int8_t)x_uint8_t;
  Serial.println("x_int8_t = (int8_t)x_uint8_t");
  Serial.println(x_int8_t);
  Serial.println("");

  float x_uint8_t_to_float = (float)x_uint8_t;
  Serial.println("(float)x_uint8_t");
  Serial.println(x_uint8_t_to_float);
  Serial.println("");

  float x_int8_t_to_float = (float)x_int8_t;
  Serial.println("x_int8_t_to_float = (float)x_int8_t");
  Serial.println(x_int8_t_to_float);
  Serial.println("");

  Serial.println("-------------------------");
  delay(5000);
}
