
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
const long interval = 500;              //ortalama sıcaklık hesaplama süresi
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const long interval2 = 2000;

double T1=0;//interval önceki sıcaklık
double T2=0;
int step1=10; //step size for inc
int step2=20;
int pos=90;


//ortalama sıcaklık için 

const int numReadings = 30;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = numReadings*20;                  // the running total
int average = 20;  

const int numReadings2 = 3;
int readings2[numReadings2];      // 2. sayaç
int readIndex2 = 0;              // 2.sayaç
int total2 = numReadings2*20;                  // 2.sayaç
int average2 = 20;  
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


//--------------------------  

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
Myservo.attach(10);

//ortalama sıcaklık
// initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 20;}
  for (int thisReading2 = 0; thisReading2 < numReadings2; thisReading2++) {
    readings2[thisReading2] = 20;}
 delay(2000);

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
// test sonu------------------

double T0=dht.readTemperature();

unsigned long currentMillis = millis();
 if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

   
  total = total - readings[readIndex];
  readings[readIndex] = T0;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) 
  {
    readIndex = 0;
  }
T1 = total / numReadings;
 }

  lcd.setCursor(0,0);
  lcd.print("sicaklik:");    //Do not display entered keys
  lcd.print(T0);
  
 
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
  lcd.print("ayar:");
  lcd.print(SetPoint);
  lcd.print("C / T1");
  lcd.setCursor(12,1);
  lcd.print(T1);


//Check T0 is in limit
if(T0 > (SetPoint+4))
{
  Myservo.write(0);
  pos=20;
   digitalWrite(RELAY,LOW);    //Turn off heater
   digitalWrite(LED_RED,LOW);
   digitalWrite(LED_GREEN,HIGH);  //Turn on Green LED
}
else if (T0<(SetPoint-4))
{
  Myservo.write(170);
  pos=90;
  digitalWrite(RELAY,HIGH);    //Turn on heater %100
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED  
}

//
else if (T0>(SetPoint-4)& T0<(SetPoint+4)& (currentMillis - previousMillis2 >= interval2) )
{
  if (T1<T0)
  {pos=(pos-step1);}
  else if (T1>T0)
  {pos = (pos+step1);}
  
  Myservo.write(pos);
  digitalWrite(RELAY,HIGH);    //Turn on heater %50
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED 
   previousMillis2 = currentMillis;
   
}
 
  delay(100); //Update at every 
  
}



 
