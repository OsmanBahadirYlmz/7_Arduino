#include <virtuabotixRTC.h>   
virtuabotixRTC myRTC(11, 12, 13);

#include <TimeLib.h>
tmElements_t tm;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Keypad.h>
#define Password_Length 8
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "123A456";

char user[][Password_Length] = {"1234567","1234568","1234569",
                                "1234561","1234562","1234563",
                                "1234565"}


unsigned long date[]Master2date,Master3date,Master4date,Master5date,
            Master6date,Master7date,Master8date,Master9date,Master10date;

// Pin connected to lock relay input
int lockOutput = 13;
 
// Counter for character entries
byte data_count = 0;
 
// Character to hold key input
char customKey;
 
// Constants for row and column sizes
const byte ROWS = 4;
const byte COLS = 4;
 
// Array to represent keys on keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
 
// Connections to Arduino
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
 
// Create keypad object
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
// Create LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

//-----stepper
#define dirPin A0
#define stepPin A1
const int stepsPerRevolution = 200;


void setup() {
  Serial.begin(9600);
  
 //lcd keypad
 // Setup LCD with backlight and initialize
  lcd.backlight();
  lcd.init();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
 
  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);

//stepper
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
}

void loop() {
  
  myRTC.updateTime();     
  Serial.print("Current Date / Time: ");                                                                 //| 
  Serial.print(myRTC.dayofmonth);                                                                        //| 
  Serial.print("/");                                                                                     //| 
  Serial.print(myRTC.month);                                                                             //| 
  Serial.print("/");                                                                                     //| 
  Serial.print(myRTC.year);                                                                              //| 
  Serial.print("  ");                                                                                    //| 
  Serial.print(myRTC.hours);                                                                             //| 
  Serial.print(":");                                                                                     //| 
  Serial.print(myRTC.minutes);                                                                           //| 
  Serial.print(":");                                                                                     //| 
  Serial.println(myRTC.seconds);  
  
//sil-------

//Serial.println("--------");
//
//  time_t nextMakeTime;
//  tm.Second = myRTC.seconds; 
//  tm.Hour = myRTC.hours;
//  tm.Minute = myRTC.minutes;
//  tm.Day = myRTC.dayofmonth;
//  tm.Month = myRTC.month;
//  tm.Year = myRTC.year - 1970;   // offset from 1970;
//  nextMakeTime =  makeTime(tm)+(86400); // convert time elements into time_t
//  Serial.println(nextMakeTime);   
//  Serial.println(day(nextMakeTime));   
//  Serial.println(month(nextMakeTime));   
//  Serial.println(year(nextMakeTime));
//  Serial.println(hour(nextMakeTime));
//
//int mm=month(nextMakeTime);
//  int dd=day(nextMakeTime);
//  int hh=hour(nextMakeTime);
//
//  unsigned long mmddhh=long(mm)*10000+long(dd)*100+hh ;                                                                                                                           
//  Serial.print("mmddhh: ");Serial.println(mmddhh);
//
//  delay(3000);

//sil------------------
   
                                                                                                         //| 
                                                                                                        
//lcd keypad

 // Initialize LCD and print
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
 
  // Look for keypress
  customKey = customKeypad.getKey();
  if (customKey) {
    // Enter keypress into array and increment counter
    Data[data_count] = customKey;
    lcd.setCursor(data_count, 1);
    lcd.print(Data[data_count]);
    data_count++;
  }
 
  // See if we have reached the password length
  if (data_count == Password_Length - 1) {
    lcd.clear();
 
    if (!strcmp(Data, Master)) {
      // Password is correct
      lcd.print("Correct-Master");
      stepDon();    
    }  
    checkPassword();
 
    }
 
    // Clear data and LCD display
    lcd.clear();
    clearData();
} 
                                                                                         //| 
 

void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}  

void stepDon(){
    digitalWrite(dirPin, LOW);
    for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(2000);
  }
  delay(2000);
}




void checkPassword(){
  time_t nextMakeTime;
  tm.Second = myRTC.seconds; 
  tm.Hour = myRTC.hours;
  tm.Minute = myRTC.minutes;
  tm.Day = myRTC.dayofmonth;
  tm.Month = myRTC.month;
  tm.Year = myRTC.year - 1970;   // offset from 1970;
  nextMakeTime =  makeTime(tm)+(86400); // convert time elements into time_t
  Serial.println(nextMakeTime);   
  Serial.println(day(nextMakeTime));   
  Serial.println(month(nextMakeTime));   
  Serial.println(year(nextMakeTime)); 

  //compare date
  int mm=month(nextMakeTime);
  int dd=day(nextMakeTime);
  int hh=hour(nextMakeTime);

  unsigned long mmddhh=long(mm)*10000+long(dd)*100+hh ;                                                                                                                           
  Serial.print("mmddhh: ");Serial.println(mmddhh);

  
  if (!strcmp(Data, Master2)) {           
      if (Master2date<mmddhh){
        lcd.print("Correct");
        Master2date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Gunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Bitti");
        delay(2000);
        }      
      }

  if (!strcmp(Data, Master3)) {           
      if (Master3date<mmddhh){
        lcd.print("Correct");
        Master3date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master4)) {           
      if (Master4date<mmddhh){
        lcd.print("Correct");
        Master4date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master5)) {           
      if (Master5date<mmddhh){
        lcd.print("Correct");
        Master5date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master6)) {           
      if (Master6date<mmddhh){
        lcd.print("Correct");
        Master6date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master7)) {           
      if (Master7date<mmddhh){
        lcd.print("Correct");
        Master7date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master8)) {           
      if (Master8date<mmddhh){
        lcd.print("Correct");
        Master8date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master9)) {           
      if (Master9date<mmddhh){
        lcd.print("Correct");
        Master9date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }
  if (!strcmp(Data, Master10)) {           
      if (Master10date<mmddhh){
        lcd.print("Correct");
        Master10date=mmddhh;
        stepDon();
        }
      else {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Dunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Dolmustur");
        delay(2000);
        }      
      }



      
  
}
