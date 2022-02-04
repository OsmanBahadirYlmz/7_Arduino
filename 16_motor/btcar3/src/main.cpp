#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10,11);

  const int motorA1  = 6;  // L298N'in IN3 Girişi
  const int motorA2  = 7;  // L298N'in IN1 Girişi
  const int motorB1  = 8; // L298N'in IN2 Girişi
  const int motorB2  = 9;  // L298N'in IN4 Girişi

void setup() {
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);
    Serial.begin(9600);
    Serial.println("enter At commands");
    BTSerial.begin(38400);


    



  // put your setup code here, to run once:
}

void loop() {

  if(BTSerial.available()) Serial.write(BTSerial.read());
  if(Serial.available()) BTSerial.write(Serial.read());


//   digitalWrite(motorA1,HIGH);
//   digitalWrite(motorA2,LOW);
//   delay(1000);
//   digitalWrite(motorA1,LOW);
//   digitalWrite(motorA2,LOW);
// for (int i=0;i<255;i++){
//   digitalWrite(motorB1,LOW);
//   analogWrite(motorB2,i);

//  delay(20);


// }

//   digitalWrite(motorB1,LOW);
//   digitalWrite(motorB2,LOW);
//   delay(2500);



  // put your main code here, to run repeatedly:
}