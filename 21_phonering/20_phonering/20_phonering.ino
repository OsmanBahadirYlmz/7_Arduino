#define magnet1 7
#define magnet2 8

void setup() {
  // put your setup code here, to run once:
  pinMode(magnet1,OUTPUT);
  pinMode(magnet2,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<15;i++){
    Serial.println("ring");
  digitalWrite(magnet1,HIGH);
  digitalWrite(magnet2,LOW);
  delay(200);
  digitalWrite(magnet1,LOW);
  digitalWrite(magnet2,HIGH);
  delay(200);
  }
    digitalWrite(magnet1,LOW);
  digitalWrite(magnet2,LOW);
delay(3000);

}
