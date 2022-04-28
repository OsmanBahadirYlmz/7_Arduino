#include <DHT.h>
#define DHTPIN D2 
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);
unsigned long currentMillis=0;
unsigned long previousMillis3 = 0;
const long interval3 = 60000; 


double T=20; //sensörden ölçülen anlık sıcaklık null olabilir
double T0=20;//anlık sıcaklık null değil
double H;



void setup() {
Serial.begin(9600);
dht.begin();
delay(2000);
}

void loop() {



T=dht.readTemperature();
H=dht.readHumidity();
if(T<70 && T>-30) T0=T;
Serial.print("T: ");Serial.println(T);
Serial.print("T0: ");Serial.println(T0);
Serial.print("H: ");Serial.println(H);


delay(1000);



}
