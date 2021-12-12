/*
Control and external RGB LED and mix colors

Christopher Lum
lum@uw.edu

Version History
10/27/21: Created
11/11/21: Updated
*/

//Constants
int PinLED_R = A5;
int PinLED_G = A4;
int PinLED_B = A3;

void setup() {
  //Serial
  Serial.begin(9600);
  
  //LED
  pinMode(PinLED_R,OUTPUT);
  pinMode(PinLED_G,OUTPUT);
  pinMode(PinLED_B,OUTPUT);
}

void loop() {
  //create arrays of brightness
  int N = 10;   //number of color partitions
  int deltaColor = (int)(floor(255.0/(float)N));  
  int brightnessLevels[N];
  for(int k=0;k<N;k++) {
    brightnessLevels[k] = k*deltaColor;
  }

  //cycle through various permutations of colors
  for(int kR=0;kR<N;kR++) {
    for(int kG=0;kG<N;kG++) {
      for(int kB=0;kB<N;kB++) {
        //Get the current RGB value
        int R_k = brightnessLevels[kR];
        int G_k = brightnessLevels[kG];
        int B_k = brightnessLevels[kB];

        Serial.println("RGB = [" + (String)R_k + "," + (String)G_k + "," + (String)B_k + "]");

        //set the color        
        analogWrite(PinLED_R,R_k);
        analogWrite(PinLED_G,G_k);
        analogWrite(PinLED_B,B_k);
        
        delay(10);
      }
    }    
  }

  delay(1000);
}
