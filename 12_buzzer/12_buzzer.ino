const int buzzer = 9; //buzzer to arduino pin 9


void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}

void loop(){
 
  tone(buzzer, 500,500); // Send 1KHz sound signal...
  digitalWrite(buzzer,LOW);
  delay(1000);
  
}
