// include the library code:
#include <LiquidCrystal.h>
#include<Servo.h>
Servo Myservo;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int LED_RED=9; //Red LED
const int LED_GREEN=8; //Green LED
const int RELAY=12; //Lock Relay or motor
const int up_key=6;
const int down_key=7;
int SetPoint=25;
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 500;              //ortalama sıcaklık hesaplama süresi
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const long interval2 = 2000;

double T1=0;//interval son 15 ölçüm ort
double T2=0;//interval son 3 ölçüm ort
int step1=10; //step size for inc
int step2=20;
int pos=90;


//ortalama sıcaklık için 

const int numReadings = 15;
int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = numReadings*20;                  // the running total
int average = 20;  

const int numReadings2 = 3;
int readings2[numReadings2];      // 2. sayaç
int readIndex2 = 0;              // 2.sayaç
int total2 = numReadings2*20;                  // 2.sayaç
int average2 = 20;  
//-----------------------
int state=0; //ortalama sıcaklığa göre durum 0->(T1=T2) , 1->(T1<T2) 2-<(T1>T2)


void setup() {
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);  
  pinMode(RELAY,OUTPUT);  
  pinMode(up_key,INPUT);
  pinMode(down_key,INPUT);
  digitalWrite(up_key,HIGH);
  digitalWrite(down_key,HIGH);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("sicaklik=");
  lcd.setCursor(0, 1);
  lcd.print("ayar=");
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

    
//----------------------------------
  
  delay(2000);
}

void loop() {
  
  double T0 = ((5.0/10240.0) * analogRead(A0)) * 100+15;  //5/1024 tü 10mV per degree 0.01V/C. Scalling
  
  unsigned long currentMillis = millis();
 if (currentMillis - previousMillis >= interval) {

    previousMillis = currentMillis;

   
  total = total - readings[readIndex];
  readings[readIndex] = T0;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;
  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  T1 = total / numReadings;
//T2 son 3 okuma-daha sağlıklı okumalar için kullanmazsan sil
  total2 = total2 - readings2[readIndex2];
  readings2[readIndex2] = T0;
  total2 = total2 + readings2[readIndex2];
  readIndex2 = readIndex2 + 1;
  if (readIndex2 >= numReadings2) {
    readIndex2 = 0;
  }
  T2 = total2 / numReadings2;
  // ---------------------------------------------
    
 }
  lcd.setCursor(0,0);
  lcd.print("C:");    //Do not display entered keys
  lcd.print(T0);
  
  //Get user input for setpoints  
  if(digitalRead(down_key)==LOW)
  {
    if(SetPoint>0)
    {
      SetPoint--;    
    }
  }
  if(digitalRead(up_key)==LOW)
  {
    if(SetPoint<150)
    {
      SetPoint++;
    }
  }
 //state kararı ortalama sıcaklığa göre durum 0->(T1=T2) , 1->(T1<T2) 2-<(T1>T2)
if(T1<(T2+1) & T1>(T2-1))
{state=0;}
else if(T1<T2)
{state=1;}
else if (T1<T2)
{state=2;}

 //----------------
//Display Set point on LCD
  lcd.setCursor(0,1);
  lcd.print("ayar:");
  lcd.print(SetPoint);
  lcd.print("C T1  ");
  lcd.setCursor(12,1);
  lcd.print(T1);
  lcd.setCursor(12,0);
  lcd.print(state);
  
//Check T0 is in limit
if(T0 > (SetPoint+3))
{
  Myservo.write(0);
  pos=20;
   digitalWrite(RELAY,LOW);    //Turn off heater
   digitalWrite(LED_RED,LOW);
   digitalWrite(LED_GREEN,HIGH);  //Turn on Green LED
}
else if (T0<(SetPoint-3))
{
  Myservo.write(170);
  pos=90;
  digitalWrite(RELAY,HIGH);    //Turn on heater %100
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED  
}

else if (T0>(SetPoint-3)& T0<(SetPoint+3)& (currentMillis - previousMillis2 >= interval2) )
{
  if (T0<(SetPoint-1))
  {switch (state)
    {
     case 0:
     pos=pos+step1;
     break;
     case 1:
     pos=pos+step1;
     break;
     case 2:
     
     break;
  
    }
  }
  else if (T0>(SetPoint+1))
  {switch (state)
    {
     case 0:
     
     break;
     case 1:
     
     break;
     case 2:
     pos=pos-step1;
     break;
  
    }
  }
  else if (T0<(SetPoint-1)& T0>(SetPoint+1) )
  {switch (state)
    {
     case 0:
     
     break;
     case 1:
     
     break;
     case 2:
     pos=pos-step1;
     break;
  
    }
  }
  Myservo.write(pos);
  digitalWrite(RELAY,HIGH);    //Turn on heater %50
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED 
   previousMillis2 = currentMillis;
   
}
 
  delay(100); //Update at every 
  
}
