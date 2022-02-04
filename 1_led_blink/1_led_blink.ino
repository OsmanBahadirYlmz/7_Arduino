void setup() {
#define ledpin 3

  pinMode(ledpin,OUTPUT);
}

void loop() {
  digitalWrite(ledpin,HIGH);
  delay(200);
  digitalWrite(ledpin,LOW);
  delay(1500);
  

}
