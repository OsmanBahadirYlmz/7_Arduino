

#define potpin A0
#include <Servo.h>
Servo motor;
int deger=0;
int derece=0;
void setup() {
  Serial.begin(9600);
  Serial.println("pot deger durumu");
  motor.attach(3);

}

void loop() {
 deger=analogRead(potpin);
 derece=map(deger, 0,1023,0,180);
 Serial.println(derece);
 motor.write(90);
 
}
