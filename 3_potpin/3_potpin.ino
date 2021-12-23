#define potpin A0
float deger=0;
void setup() {
  Serial.begin(9600);
  Serial.println("pot deger durumu");

}

void loop() {
 deger=analogRead(potpin);
 deger=deger*5/1024;
 Serial.println(deger);

}
