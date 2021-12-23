/* 
   circuits4you.com
   Digital Temperature Controller
*/
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(9, 8, 7, 6, 5, 4);
 
const int LED_RED=10; //Red LED
const int LED_GREEN=11; //Green LED
const int RELAY=12; //Lock Relay or motor
 
//Key connections with arduino
const int up_key=3;
const int down_key=2;
 
int SetPoint=30;
//=================================================================
//                  SETUP
//=================================================================
void setup(){
  pinMode(LED_RED,OUTPUT);
  pinMode(LED_GREEN,OUTPUT);  
  pinMode(RELAY,OUTPUT);  
  pinMode(up_key,INPUT);
  pinMode(down_key,INPUT);
  
  //Pull up for setpoint keys
  digitalWrite(up_key,HIGH);
  digitalWrite(down_key,HIGH);
  
   // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("circuits4you.com");  
  lcd.setCursor(0,1); //Move coursor to second Line
  lcd.print("Temp. Controller");
  digitalWrite(LED_GREEN,HIGH);  //Green LED Off
  digitalWrite(LED_RED,LOW);     //Red LED On
  digitalWrite(RELAY,LOW);       //Turn off Relay
  delay(2000);
}
//=================================================================
//                  LOOP
//=================================================================  
void loop(){
  double Temperature = ((5.0/1024.0) * analogRead(A0)) * 100;  //10mV per degree 0.01V/C. Scalling
 
  lcd.setCursor(0,0);
  lcd.print("Temperature:");    //Do not display entered keys
  lcd.print(Temperature);
  
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
  lcd.print("Set Point:");
  lcd.print(SetPoint);
  lcd.print("C   ");
 
//Check Temperature is in limit
if(Temperature > SetPoint)
{
   digitalWrite(RELAY,LOW);    //Turn off heater
   digitalWrite(LED_RED,LOW);
   digitalWrite(LED_GREEN,HIGH);  //Turn on Green LED
}
else
{
  digitalWrite(RELAY,HIGH);    //Turn on heater
  digitalWrite(LED_GREEN,LOW);
  digitalWrite(LED_RED,HIGH);  //Turn on RED LED  
}
 
  delay(100); //Update at every 100mSeconds
}
