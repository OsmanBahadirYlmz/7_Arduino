                                                                                                         //|
#include <virtuabotixRTC.h>                                                                              //|
                                                                                                         //|

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);

//-------------lcd keypad-----------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#define Password_Length 8
// Character to hold password input
char Data[Password_Length];
// Password
char Master[Password_Length] = "123A456";

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
LiquidCrystal_I2C lcd(0x3F, 16, 2);


//******************************************************************
//******************************************************************
void setup()  {      
  Serial.begin(9600);

// Set the current date, and time in the following format:
// seconds, minutes, hours, day of the week, day of the month, month, year
  myRTC.setDS1302Time(00, 59, 23, 6, 10, 1, 2014);


//lcd keypad
 // Setup LCD with backlight and initialize
  lcd.backlight();
  lcd.init();
 
  // Set lockOutput as an OUTPUT pin
  pinMode(lockOutput, OUTPUT);

  
}

                                                                                                       //|   
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//|  
void loop()  {                                                                                           //| 
// This allows for the update of variables for time or accessing the individual elements.                //|
  myRTC.updateTime();                                                                                    //| 
                                                                                                         //| 
// Start printing elements as individuals                                                                //|   
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
  Serial.println(myRTC.seconds);                                                                         //| 

  int mm=myRTC.month
  int dd= myRTC.dayofmonth
  int hh= myRTC.hours

  unsigned long mmddhh=long(mm)*10000+long(dd)*100+hh                                                                                                                            
                                                                                                         
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
      lcd.print("Correct");
      // Turn on relay for 5 seconds
      digitalWrite(lockOutput, HIGH);
      delay(5000);
      digitalWrite(lockOutput, LOW);
    }
    else {
      // Password is incorrect
      lcd.print("Incorrect");
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
