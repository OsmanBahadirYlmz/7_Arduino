    /*   
modified on Sep 27, 2020
Modified by MohammedDamirchi from https://github.com/mikalhart/TinyGPSPlus
Home 
*/ 

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPS++ (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   9600-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

//timer
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//distance calculation
float start_lat, start_lon, flat, flon;
unsigned long age, date, time, chars = 0;
unsigned short sentences = 0, failed = 0;
double s_latitude=39 ;  
double s_longitude=27 ;
double f_latitude ;   
double f_longitude ;
unsigned long sum_distance1=0;
unsigned long sum_distance2=0;


#include <math.h>


////oled
//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SH110X.h>
//
///* Uncomment the initialize the I2C address , uncomment only one, If you get a totally blank screen try the other*/
//#define i2c_Address 0x3c //initialize with the I2C addr 0x3C Typically eBay OLED's
////#define i2c_Address 0x3d //initialize with the I2C addr 0x3D Typically Adafruit OLED's
//
//#define SCREEN_WIDTH 128 // OLED display width, in pixels
//#define SCREEN_HEIGHT 64 // OLED display height, in pixels
//#define OLED_RESET -1   //   QT-PY / XIAO
//Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  




//oled
//  Serial.println("Start oled");
//  display.begin(i2c_Address, true); // Address 0x3C default
//  Serial.println("Error Here");
//  display.clearDisplay();
//  display.setTextSize(1);
//  display.setTextColor(SH110X_WHITE);
//  display.setCursor(0, 0);
//  display.println("Mesafe Olcer");
//
//
//  display.setCursor(0, 20);
//  display.println("v2");
//  display.display();
//  delay(2000);

  


}


double haversine(double lat1, double lon1, double lat2, double lon2) {
    const double rEarth = 6371000.0; // in meters
    double x = pow( sin( ((lat2 - lat1)*M_PI/180.0) / 2.0), 2.0 );
    double y = cos(lat1*M_PI/180.0) * cos(lat2*M_PI/180.0);
    double z = pow( sin( ((lon2 - lon1)*M_PI/180.0) / 2.0), 2.0 );
    double a = x + y * z;
    double c = 2.0 * atan2(sqrt(a), sqrt(1.0-a));
    double d = rEarth * c;
    // Serial.printlnf("%12.9f, %12.9f, %12.9f, %12.9f, %12.9f, %12.9f", x, y, z, a, c, d);
    return d; // in meters
}





void displayInfo(){
  Serial.println("----------------------");

  
    f_latitude = gps.location.lat();   
    f_longitude = gps.location.lng();

   unsigned long distance=
    (unsigned long)TinyGPSPlus::distanceBetween(
      f_latitude,
      f_longitude,
      s_latitude,
      s_longitude);

     if (distance<200 && distance>0) sum_distance1+=distance;
//   unsigned long distance2=
//    (unsigned long)TinyGPSPlus::distanceBetween(
//      39,
//      27,
//      35,
//      29) ;
////
//unsigned long distance3=haversine(39,27,39.001,27.002);

     
    Serial.print("s_latitude");Serial.println(s_latitude,6);
    Serial.print("s_longitude");Serial.println(s_longitude,6);
    Serial.print("f_latitude");Serial.println(f_latitude,6);
    Serial.print("f_longitude");Serial.println(f_longitude,6);
    Serial.print("distance  :");Serial.println(distance,9);
//    Serial.print("distance2  :");Serial.println(distance2,9);
//    Serial.print("distance3  :");Serial.println(distance3,9);
    Serial.print("sum_distance1  :");Serial.println(sum_distance1,9);
      
     s_latitude =  f_latitude ;
     s_longitude = f_longitude;



    
  Serial.println("----------------------");

  
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6 );
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();  
  

  
  }
void loop(){
  //   collect data every 3 sec
 

    
 
    while (ss.available() > 0){
      currentMillis=millis();
      if (gps.encode(ss.read()) && (  currentMillis - previousMillis >= 3000 ) ){
        displayInfo();
        previousMillis=millis();
      }
    
    if (millis() > 5000 && gps.charsProcessed() < 10)
      {
        Serial.println(F("No GPS detected: check wiring."));
        while(true);
      }
   }
}
