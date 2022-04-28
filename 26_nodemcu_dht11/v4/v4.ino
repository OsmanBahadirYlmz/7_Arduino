#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;

#include <OneWire.h> // OneWire kütüphanesini ekliyoruz.

// Sıcaklık Sensörü Giriş-Çıkışı
OneWire ds(D7);  

//-------------wifi ayarları---------------

#include <ESP8266WiFi.h>
String apiKey = "P4YE444CA415ZOTT";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "Superbox_WiFi_B5D6";     // replace with your wifi ssid and wpa2 key
const char *pass =  "BGGLJQM21Y9";
const char* server = "api.thingspeak.com";
WiFiClient client;
int counter=0;//when connection fails

//----------------------------------------




void setup(void) {
    Serial.begin(9600); // Seri iletişimi başlatıyoruz.
  
    lcd.begin(16, 2);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cihaz Aciliyor");
    lcd.setCursor(0,1);
    lcd.print("v4");
    delay(2000);
    

//-------------wifi ayarları---------------
    Serial.println("Connecting to ");
   Serial.println(ssid);


   WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) 
   {
          counter++;
          if (counter>100){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("--wifi hatasi!--");
            delay(2000);
            lcd.clear();
            break;

            
          }
          delay(500);
          Serial.print(".");
          lcd.setCursor(0,1);
          lcd.print("wifi araniyor");
          
          
   }
    Serial.println("");
    Serial.println("WiFi connected");
    lcd.clear();


//----------------------------------------


    
}

void loop(void) {
  // temperature değişkenini sıcaklık değerini alma fonksiyonuna bağlıyoruz.
  float temperature = getTemp();
  // Sensörden gelen sıcaklık değerini Serial monitörde yazdırıyoruz.
  Serial.print("Sicaklik: ");
  Serial.println(temperature);

  
//LCD yazım  
  lcd.setCursor(0,0);
  lcd.print("Sicaklik");
  lcd.setCursor(0,1);
  lcd.print(temperature);
  lcd.print(" C");

//wifi

//-------------wifi ayarları---------------
  float h = 50;
  float t = temperature;
  if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting..."); 


 


//----------------------------------------

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
