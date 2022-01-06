#include <Arduino.h>

void setup() {
  pinMode(9,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  digitalWrite(9,HIGH);
  delay(2500);
  digitalWrite(9,LOW);
  delay(300);
  Serial.println("loop");
  
  // put your main code here, to run repeatedly:
}