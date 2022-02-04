byte incomingByte1;
#define led 2
 void setup(){
  pinMode(2,OUTPUT);
  Serial.begin(9600);
  Serial.println("Ready"); 

  

}
 void loop() {
  digitalWrite(2,LOW); //turn off LED
  delay(500);
if (Serial.available() > 0) { 
 digitalWrite(2,HIGH); //flash LED everytime data is available
 delay(500);
 incomingByte1 = Serial.read(); //read incoming data
 Serial.println(incomingByte1,HEX); //print data
}
}
