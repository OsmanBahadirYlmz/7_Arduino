void setup() {
#define fc33 2

  pinMode(fc33,INPUT);
  Serial.begin(9600);
}

void loop() {
 
 int s=digitalRead(fc33);
 Serial.println(s);
 


}
