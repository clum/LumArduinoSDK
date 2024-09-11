/*
Send messages on serial.

Christopher Lum
lum@uw.edu

Version History
09/10/24: created
*/

//Constants

void setup() {
  //Serial
  Serial.begin(9600);
}

void loop() {
  int k = 0;
  while(1) {
    String myString = "Counter = ";

    //Add to the string, include a terminator char
    myString = myString + k + "\n"; 
    
    Serial.print(myString);
    delay(1000);
    
    k = k + 1;
  }
}
