

#define potpin A0
#include <Servo.h>

#include <Wire.h>
#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2 
#define DHTTYPE    DHT11 
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int dht_read=0;
Servo motor;
int deger=0;
int derece=0;



void setup() {
  Serial.begin(9600);
  Serial.println("pot deger durumu");
  motor.attach(3);

  lcd.begin(16, 2);
  lcd.print("vs code prog");
  delay(2000);

  dht.begin();
  sensor_t sensor;
}

void loop() {
 deger=analogRead(potpin);

 derece=map(deger, 0,1023,0,180);
 Serial.println(dht_read);
 motor.write(derece);

//DHT sensör okuma
delay(1000);
sensors_event_t event;
dht.temperature().getEvent(&event);
Serial.print(F("Temperature: "));
Serial.print(event.temperature);
Serial.println(F("°C"));
lcd.setCursor(0,0);
lcd.print(event.temperature);

dht.humidity().getEvent(&event);
Serial.print(F("Humidity: "));
Serial.print(event.relative_humidity);
Serial.println(F("%"));
lcd.setCursor(0,1);
lcd.print(event.relative_humidity);


}
