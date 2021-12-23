#define potpin A0
#define led 3
float deger=0;
void setup() {
  Serial.begin(9600);
  Serial.println("pot deger durumu");

}

void loop() {
 deger=analogRead(potpin);
 deger=deger/4;
 Serial.println(deger);
 analogWrite(led,deger);
 
}
