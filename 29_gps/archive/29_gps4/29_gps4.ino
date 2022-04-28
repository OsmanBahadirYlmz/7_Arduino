#include <SoftwareSerial.h>

#include <TinyGPS.h>


TinyGPS gps;
SoftwareSerial ss(3, 4);

//distance
float slat=39;
float slon=27;
unsigned long age=0;
unsigned long sum_distance1=0;
unsigned long sum_distance2=0;
int distance=0;

//timer
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//sensor
#define sensorpin A0
int sensor;

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);



void setup()
{
  Serial.begin(115200);
  
  ss.begin(9600);

  pinMode(sensorpin,INPUT);

  //opening screen
  u8g.firstPage();
    do {
      u8g.setFont(u8g_font_profont12);
      u8g.setPrintPos(0, 10);
      u8g.print("Mesafe Olcer");         
      u8g.setPrintPos(0, 25);
      u8g.print("v4");      
      u8g.setPrintPos(0, 40);        
      

    } while (u8g.nextPage() );
    delay(2000);
  

//gps bağlanma beklemesi
int counter=0;
  while(1){
    smartdelay(1000);
    gps.f_get_position(&slat, &slon, &age);  
    Serial.print("slat: "); Serial.println(slat,6);
    Serial.print("slon: "); Serial.println(slon,6);   
    if(slat>1 && slat<100) break;

    
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_profont12);
      u8g.setPrintPos(0, 10);
      u8g.print("GPS Sinyali Araniyor");         
      u8g.setPrintPos(counter*3, 25);
      u8g.print("*");
      } while (u8g.nextPage() );
    delay(2000);
    counter++;
    
  }
  
}

void loop()
{
  Serial.println("--------------------");

  
  smartdelay(1000);

  uint8_t sat =gps.satellites();
  Serial.print("sat: "); Serial.println(sat);

  float flat, flon;
  unsigned long age;
  gps.f_get_position(&flat, &flon, &age);
  Serial.print("flat: "); Serial.println(flat,6);
  Serial.print("flon: "); Serial.println(flon,6);
  Serial.print("slat: "); Serial.println(slat,6);
  Serial.print("slon: "); Serial.println(slon,6);

  float spd=gps.f_speed_kmph();
  Serial.print("spd "); Serial.println(spd);

  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age2;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);
  hour+=3;if(hour>=24)hour-=24;

  // sensordeğeri okuma
  sensor=analogRead(sensorpin);
  Serial.print("sensor: "); Serial.println(sensor);


 
  //distance measurement
  currentMillis=millis();
  if(currentMillis - previousMillis >= 10000){
    distance = TinyGPS::distance_between(flat, flon, slat, slon);
    if (distance>250 || distance<0 ) distance=0; //set distance 0 if measure larger
    
    if(distance>15){
      slat=flat;
      slon=flon;
      sum_distance1=sum_distance1+distance;
      if (sensor>350 ) sum_distance2=sum_distance2+distance;
      Serial.print("sum_distance1: "); Serial.println(sum_distance1);
      Serial.print("sum_distance2: "); Serial.println(sum_distance2);
    }
    
      Serial.print("distance "); Serial.println(distance);
    


    previousMillis=currentMillis;
  }



//print oled  
   u8g.firstPage();
    do {
      u8g.setFont(u8g_font_profont12);
      u8g.setPrintPos(0, 10);
      u8g.print(sat);
      u8g.setPrintPos(64, 10);
      u8g.print(distance);
      
      
      u8g.setPrintPos(0, 25);
      u8g.print(hour);
      u8g.setPrintPos(10, 25);
      u8g.print(":");
      u8g.setPrintPos(20, 25);
      u8g.print(minute);

      if (sensor>350){
        u8g.setPrintPos(64, 25);
        u8g.print("++++");
      }
      
      u8g.setPrintPos(0, 40);
      u8g.print("top: "); u8g.print(sum_distance1);
      u8g.setPrintPos(64, 40);
      u8g.print("sen: "); u8g.print(sum_distance2);

      //hız
      u8g.setPrintPos(0, 55);
      u8g.print("hiz: ");
      u8g.print(spd);

    //sensör verisi
      u8g.setPrintPos(64, 55);
      u8g.print("s_val: ");
      u8g.print(sensor);
    
      
    } while (u8g.nextPage() );
    delay(10);
  
//  u8g.firstPage();
//  do {
//    draw2();
//  } while (u8g.nextPage());
//  delay(3500);


  
}

static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
