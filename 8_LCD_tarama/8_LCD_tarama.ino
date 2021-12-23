#include <Wire.h>

void setup() 
{
  Serial.begin(9600);
  Serial.print("ı2c taranıyor...");
  Wire.begin();
  for (byte e=8;e<150;e++)
  {
    Wire.beginTransmission(e);
    if(Wire.endTransmission()==0)
    {
      Serial.print("iletişim yolu bulundu, Ekran türü:");
      Serial.print(e,DEC);
      Serial.print("(0x");
      Serial.print(e,HEX);
      Serial.print(")");
    } 
  }  
  Serial.println("Tamamlandı.");
}

void loop() {
  // put your main code here, to run repeatedly:

}
