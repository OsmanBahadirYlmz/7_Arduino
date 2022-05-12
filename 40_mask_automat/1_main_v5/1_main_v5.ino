#include <virtuabotixRTC.h>   
virtuabotixRTC myRTC(11, 12, 13);

#include <TimeLib.h>
tmElements_t tm;
unsigned long next_mmddhh;
unsigned long mmddhh;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Keypad.h>
#define Password_Length 8
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "123A456";

char user[10][Password_Length] = {"1234567","1234568","1234569",
                                "1234561","1234562","1234563",
                                "1234564","1234565","1234566",
                                "1234560"};

unsigned long date2[10]={000000,000000,000000,
                        000000,000000,000000,000000,
                        000000,000000,000000};

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
  lcd.print("Maske Otomati");
  delay(3000);
 
  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);

  //stepper
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  //test
  for (int i=0; i<10;i++){
    Serial.println(user[i]);
    Serial.println(date2[i]);
  }
  
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


   
                                                                                                         //| 
  int mm=myRTC.month;
  int dd= myRTC.dayofmonth;
  int hh= myRTC.hours;

  mmddhh=long(mm)*10000+long(dd)*100+hh ;                                                                                                                           
  Serial.print("mmddhh: ");Serial.println(mmddhh);                                                                                                      
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

    checkPassword();
 
    if (!strcmp(Data, Master)) {
      // Password is correct
      lcd.print("Master-Correct");
      // Turn on relay for 5 seconds
      
      delay(1000);
      
    }
  
 
    // Clear data and LCD display
    lcd.clear();
    clearData();
  } 
                                                                                         //| 
}  

void clearData() {
  // Go through array and clear data
  while (data_count != 0) {
    Data[data_count--] = 0;
  }
  return;
}   

void checkPassword(){

  Serial.println("checkpasword");

  for(int i=0;i<10;i++){
    if(!strcmp(Data, user[i])){
      Serial.println("kod doğru");
      
      if(date2[i]<mmddhh){
        checkDate();
        date2[i]=next_mmddhh;
        

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Maske Verildi");
        
        Serial.print("maske verildi-i: ");Serial.println(i);

        stepDon();
        delay(500);
        return;
      }

      else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Gunluk Kullanim");
        lcd.setCursor(0,1);
        lcd.print("Hakkiniz Bitti");
        delay(2000);
        return;
        
      }
    }
    
  }//for loop
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hatali Sifre");
  delay(2000);
  return;
  
}//chck password

void checkDate(){

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

  next_mmddhh=long(mm)*10000+long(dd)*100+hh ;                                                                                                                           
  Serial.print("next_mmddhh: ");Serial.println(next_mmddhh);


  
}

void stepDon(){
    Serial.println("--------STEP-------");
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











         
