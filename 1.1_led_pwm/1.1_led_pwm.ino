void setup() {
#define ledpin 2

  pinMode(ledpin,OUTPUT);
}

void loop() {
  for (int i=0;i<200;i++){
    analogWrite(ledpin,i);
    delay(10);
  }


}
