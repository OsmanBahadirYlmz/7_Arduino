void setup() {
 pinMode(A2,INPUT);
 Serial.begin(9600);
 pinMode(A0,INPUT);
 pinMode(2,INPUT);

}

void loop() {
  Serial.print(analogRead(A2));Serial.print("\t");
  Serial.print(analogRead(A0));Serial.print("\t");
  Serial.println(digitalRead(2));
  delay(200);

}
