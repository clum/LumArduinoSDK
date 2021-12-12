/*
Examples using arrays

Christopher Lum
lum@uw.edu

Version History
12/07/21: created
*/

void setup() {
  //Serial
  Serial.begin(9600);  
}

void loop() {
  int vec_int[] = {2, 2, 3, 4, 5};
  long vec_long[] = {2, 2, 3, 4, 5};
  float vec_float[] = {2, 2, 3, 4, 5};
  double vec_double[] = {2, 2, 3, 4, 5};

  //compute the average
  int sum_int = 0;
  long sum_long = 0;  
  float sum_float = 0;
  double sum_double = 0;
  
  for(int k=0;k<5;k++)
  {
    sum_int = sum_int + vec_int[k];
    sum_long = sum_long + vec_long[k];    
    sum_float = sum_float + vec_float[k];     
    sum_double = sum_double + vec_double[k];
  }

  int ave_int = sum_int/5;
  long ave_long = sum_long/5;
  float ave_float = sum_float/5;
  double ave_double = sum_double/5;

  Serial.println("sum_int = "+(String)sum_int);
  Serial.println("ave_int = "+(String)ave_int);
  Serial.println("");
  
  Serial.println("sum_long = "+(String)sum_long);
  Serial.println("ave_long = "+(String)ave_long);
  Serial.println("");

  Serial.println("sum_float = "+(String)sum_float);
  Serial.println("ave_float = "+(String)ave_float);
  Serial.println("");

  Serial.println("sum_double = "+(String)sum_double);
  Serial.println("ave_double = "+(String)ave_double);
  Serial.println("");
  
  delay(3000);
}
