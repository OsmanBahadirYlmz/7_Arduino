#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;


#include <OneWire.h> // OneWire kütüphanesini ekliyoruz.
// Sıcaklık sensörünü bağladığımız dijital pini 2 olarak belirliyoruz.
int DS18S20_Pin = 4; 
// Sıcaklık Sensörü Giriş-Çıkışı
OneWire ds(DS18S20_Pin);  // 2. Dijital pinde.



void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);  

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("On Isik Acma");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");
}

void loop() {
    float temperature = getTemp();
  // Sensörden gelen sıcaklık değerini Serial monitörde yazdırıyoruz.
  Serial.print("Sicaklik: ");
  Serial.println(temperature);
  // 1 saniye bekliyoruz. Monitörde saniyede 1 sıcaklık değeri yazmaya devam edecek.
  delay(1000);

}

float getTemp(){
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
      //no more sensors on chain, reset search
      ds.reset_search();
      return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE); // Read Scratchpad

  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;

}
