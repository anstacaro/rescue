#include "motores.h"

void setup() {
  Serial.begin(9600);
  motorsetup(); 


  // put your setup code here, to run once:

}

void loop() {
  motor(100,100); 
  delay(500); 
  motor(50,50); 
  delay(500); 
  motor(-50,-50); 
  delay(500); 
  motor(50,-50); 
  delay(200); 
  motor(-50,50); 
  delay(200); 
  // put your main code here, to run repeatedly:

}
