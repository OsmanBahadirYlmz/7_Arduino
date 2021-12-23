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
const long interval = 6000;
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const long interval2 = 2000;

double T1=0;//interval önceki sıcaklık
int step1=10; //step size for inc
int step2=20;
int pos=90;


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
  delay(2000);
}

void loop() {
  
  double T0 = ((5.0/10240.0) * analogRead(A0)) * 100+15;  //5/1024 tü 10mV per degree 0.01V/C. Scalling
  
  unsigned long currentMillis = millis();
 if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    T1= T0;
 }
  lcd.setCursor(0,0);
  lcd.print("sicaklik:");    //Do not display entered keys
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
 
//Display Set point on LCD
  lcd.setCursor(0,1);
  lcd.print("ayar:");
  lcd.print(SetPoint);
  lcd.print("C T1  ");
  lcd.setCursor(12,1);
  lcd.print(T1);
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
