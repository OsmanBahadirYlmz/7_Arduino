
#include <Wire.h>
#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN 2 
#define DHTTYPE    DHT11 
DHT dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

//wifi eklentilerli
#include <SoftwareSerial.h>
String agAdi="TURKSAT-KABLONET-70A3-2.4G";
String agSifresi="d12e9410";
int rxPin=10;
int txPin=11;
String ip= "184.106.153.149";
float sicaklik, nem;
SoftwareSerial esp(rxPin,txPin);
unsigned long previousMillis3 = 0;
const long interval3 = 20000; 


#include<Servo.h>
Servo Myservo;

const int LED_RED=9; //Red LED
const int LED_GREEN=8; //Green LED
const int RELAY=12; //Lock Relay or motor
const int up_key=7;
const int down_key=6;
// #define up_key 8
// #define down_key 7
// #define LED_RED 9
// #define LED_GREEN 8
int SetPoint=25;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;              //ortalama sıcaklık hesaplama süresi
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const long interval2 = 10000;          //wait time before make new action

double T0=20;//anlık sıcaklık
double T1=20.5;//interval önceki sıcaklık
double T2=20.6;
int step1=10; //step size for inc
int step2=20;
int pos=90;


//ortalama sıcaklık için 

const int numReadings = 60;
double readings[numReadings];      // array the readings from the analog input
int readIndex = 0;              // the index of the current reading                 
double average = 20.5;  
double total = numReadings*average;// the running total

const int numReadings2 = 10;
double readings2[numReadings2];      // 2. sayaç
int readIndex2 = 0;              // 2.sayaç
double average2 = 20.7; 
double total2 = numReadings2*average2;                  // 2.sayaç 
//test-----------------------
int a=0;

//test----------



void setup() {
  
pinMode(LED_RED,OUTPUT);
pinMode(LED_GREEN,OUTPUT);  
pinMode(RELAY,OUTPUT);  
pinMode(up_key,INPUT);
pinMode(down_key,INPUT);
digitalWrite(up_key,HIGH);
digitalWrite(down_key,HIGH);

Serial.begin(9600);

lcd.begin(16, 2);
// Print a message to the LCD.
lcd.print("sicaklik=");
lcd.setCursor(0, 1);
lcd.print("ayar=");

dht.begin();
sensor_t sensor;

digitalWrite(LED_GREEN,HIGH);  //Green LED Off
digitalWrite(LED_RED,LOW);     //Red LED On
digitalWrite(RELAY,LOW);       //Turn off Relay
Myservo.attach(5);

//ortalama sıcaklık
// initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 20;}
  for (int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++) {
    readings2[thisReading2] = 20;}

//wifi setup --------------------------
Serial.println("Started");
  esp.begin(115200);                                          //ESP8266 ile seri haberleşmeyi başlatıyoruz.
  esp.println("AT");                                          //AT komutu ile modül kontrolünü yapıyoruz.
  Serial.println("AT Yollandı");
  while(!esp.find("OK")){                                     //Modül hazır olana kadar bekliyoruz.
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadı.");
  }
  Serial.println("OK Komutu Alındı");
  esp.println("AT+CWMODE=1");                                 //ESP8266 modülünü client olarak ayarlıyoruz.
  while(!esp.find("OK")){                                     //Ayar yapılana kadar bekliyoruz.
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapılıyor....");
  }
  Serial.println("Client olarak ayarlandı");
  Serial.println("Aga Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    //Ağımıza bağlanıyoruz.
  while(!esp.find("OK"));                                     //Ağa bağlanana kadar bekliyoruz.
  Serial.println("Aga Baglandi.");



 delay(2000);

}

void Turnoff(){
 Myservo.write(0);
 delay(3000);
  
   digitalWrite(RELAY,LOW);    //Turn off heater
   digitalWrite(LED_RED,LOW);
   digitalWrite(LED_GREEN,HIGH);  //Turn on Green LED

}

void Turnon(){


 Myservo.write(170);
 delay(3000);
  
  digitalWrite(RELAY,HIGH);    //Turn on heater %100
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED  

}


void servopos(int position){
    Serial.print("servopos cagirildi---+++--+++---:");Serial.println(position);
    Myservo.write(position);
    delay(2000);
    digitalWrite(RELAY,HIGH);    //Turn on heater %50
    digitalWrite(LED_GREEN,HIGH);
    digitalWrite(LED_RED,HIGH);  //Turn on RED LED 
    

}


void loop() {

//Buton led test

//   if(digitalRead(up_key)==1){
//      digitalWrite(LED_RED,HIGH);
//       digitalWrite(LED_GREEN,HIGH);
//     }
//   else{
//     digitalWrite(LED_RED,LOW);
//     digitalWrite(LED_GREEN,LOW);
//     }

//   if(digitalRead(down_key)==1){
//      digitalWrite(LED_GREEN,HIGH);
//     }
//   else{
//     digitalWrite(LED_GREEN,LOW);
//     }
    
//Servo test
// Myservo.write(a);
// delay(1000);
// if (a<180) a=a+20;
//dht lcd yazdırma
// float temp=dht.readTemperature();
// float hum=dht.readHumidity();
// lcd.setCursor(7,0);
// lcd.print(temp);
// lcd.setCursor(7,1);
// lcd.print(hum);
// Serial.println(temp);
// Serial.println(hum);
Serial.print("pos");Serial.println(pos);
Serial.print("T0");Serial.println(T0);
Serial.print("total");Serial.println(total);
Serial.print("T1");Serial.println(T1);
Serial.print("readings");
for (int i = 0; i < 30; i++) Serial.print(readings[i]);
Serial.println("------------");


// test sonu------------------

T0=dht.readTemperature();

unsigned long currentMillis = millis();

//Ortalama sıcaklık T1 array hesaplama
 if (currentMillis - previousMillis >= interval) 
 {
  Serial.print("calc_t1 cagirildi read index:");Serial.println(readIndex);
  previousMillis = currentMillis;  
  total = total - readings[readIndex];
  readings[readIndex] = T0;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) 
    {
      readIndex = 0;
    }
  T1 = float(total) / float(numReadings);
//ortalama sıcaklık için t2 hesaplama. anlık karar verdiği için hesaplandı
  Serial.print("calc_t2 cagirildi read index:");Serial.println(readIndex2);
  previousMillis = currentMillis;  
  total2 = total2 - readings2[readIndex2];
  readings2[readIndex2] = T0;
  total2 = total2 + readings2[readIndex2];
  readIndex2 = readIndex2 + 1;
  if (readIndex2 >= numReadings2) 
    {
      readIndex2 = 0;
    }
  T2 = float(total2) / float(numReadings2);


  }

//lcd ön işlem
  lcd.setCursor(0,0);
  lcd.print("oda:");    //Do not display entered keys
  lcd.setCursor(4,0);
  lcd.print(T0); 
  lcd.setCursor(10,0);
  lcd.print(T2); 
  lcd.setCursor(15,0);
   if (T2>T1) lcd.print("+");
  if (T1>T2) lcd.print("-");
  {
    /* code */
  }
  
  
 
  //Get user input for setpoints  
  if(digitalRead(down_key)==1)
  {
    if(SetPoint>15)
    {
      SetPoint--;    
    }
  }
  if(digitalRead(up_key)==1)
  {
    if(SetPoint<30)
    {
      SetPoint++;
    }
  }


 //Display Set point on LCD
  lcd.setCursor(0,1);
  lcd.print("set:");
  lcd.print(SetPoint);
  lcd.print(" T1:");
  lcd.setCursor(11,1);
  lcd.print(T1);


//Check T2 is in limit
if(T2 > (SetPoint+4)) 
  {
  Turnoff();
  }
else if (T2<(SetPoint-4))
  {
  Turnon();
  }


//AKILLI KARŞILAŞTIRMA
//eğer oda istenenden biraz sıcaksa
if ((T2>(SetPoint)) && (currentMillis - previousMillis2 >= interval2) )
  {
    //ve oda ısınıyorsa
    if ((T1<T2)&&(pos>step1))
    {     
        pos=(pos-step1);   
        Serial.print("biraz sicak");Serial.println(pos);
        servopos(pos) ;

    }
    //ve oda soğuyorsa

    previousMillis2 = currentMillis;
  }

  //eğer oda istenenden biraz soğuksa
if ( (T2<SetPoint) && (currentMillis - previousMillis2 >= interval2) )
  {
   //VE ODA SOĞUYORSA
    if ((T1>T2)&&(pos<170))
    {
      pos = (pos+step1);
      Serial.print("biraz soguk");Serial.println(pos);
      servopos(pos);
    }
    
    previousMillis2 = currentMillis;
  }

//wifi setup veri gönderme
if (currentMillis - previousMillis3 >= interval3)
{
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           //Thingspeak'e bağlanıyoruz.
  if(esp.find("Error")){                                      //Bağlantı hatası kontrolü yapıyoruz.
    Serial.println("AT+CIPSTART Error");
  }
  //DHT11.read(dht11Pin);
  sicaklik = (float)dht.readTemperature();;
  //nem = (float)DHT11.humidity;
  String veri = "GET https://api.thingspeak.com/update?api_key=VAWRNI7PQE6P7RJN";   //Thingspeak komutu. Key kısmına kendi api keyimizi yazıyoruz.                                   //Göndereceğimiz sıcaklık değişkeni
  veri += "&field1=";
  veri += String(sicaklik);
 //veri += "&field2=";
 // veri += String(nem);                                        //Göndereceğimiz nem değişkeni
  veri += "\r\n\r\n"; 
  esp.print("AT+CIPSEND=");                                   //ESP'ye göndereceğimiz veri uzunluğunu veriyoruz.
  esp.println(veri.length()+2);
  delay(2000);
  if(esp.find(">")){                                          //ESP8266 hazır olduğunda içindeki komutlar çalışıyor.
    esp.print(veri);                                          //Veriyi gönderiyoruz.
    Serial.println(veri);
    Serial.println("Veri gonderildi.");
    delay(1000);
  }
  Serial.println("Baglantı Kapatildi.");
  esp.println("AT+CIPCLOSE");                                //Bağlantıyı kapatıyoruz
  previousMillis3 = currentMillis;


}






  delay(100); //Update at every 
  
}



 
