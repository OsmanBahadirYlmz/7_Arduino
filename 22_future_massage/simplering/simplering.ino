int motor1pin1 = 7;
int motor1pin2 = 8;



void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:   
   
  for (int i=0; i<18;i++){
   Serial.print("ring");Serial.println("");
   digitalWrite(motor1pin1, HIGH);
   digitalWrite(motor1pin2, LOW);
   delay(70);
   digitalWrite(motor1pin1, LOW);
   digitalWrite(motor1pin2, HIGH);
 
  delay(70);

  }
   digitalWrite(motor1pin1, LOW);
   digitalWrite(motor1pin2, LOW);
  delay(3000);
}
