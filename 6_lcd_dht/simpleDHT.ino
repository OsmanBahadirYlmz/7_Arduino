#include "DHT.h"
#define DHTPIN 2 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
double T;
double H;


void setup() {
    Serial.begin(9600);
    dht.begin();
    delay(1000);
}

void loop() {
T=dht.readTemperature();
H=dht.readHumidity();
Serial.print("temp  :");Serial.println(T);
Serial.print("Hum   :");Serial.println(H);
delay(500);
}
