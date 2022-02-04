const int buzzer = 11; //buzzer to arduino pin 9


void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  Serial.begin(9600);

}

void loop(){
  analogWrite(buzzer,1);
  Serial.println("analog");
  delay(1500);
  
  tone(buzzer, 500); // Send 1KHz sound signal...
  Serial.println("buzzerON");
  delay(1000);
  noTone(buzzer);
  Serial.println("buzzerLOW");
  delay(1000);
  
}
