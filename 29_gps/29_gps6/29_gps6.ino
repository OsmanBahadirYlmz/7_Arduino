#include <SoftwareSerial.h>

#include <TinyGPS.h>



TinyGPS gps;
SoftwareSerial ss(3, 4);

//distance
float slat=39;
float slon=27;
unsigned long age=0;
unsigned long sum_distance1;
unsigned long sum_distance2;
int distance=0;

//timer
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;

//sensor
#define sensorpin A0
int sensor;

#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

//--------------RFID
#include <SPI.h>                          //SPI kütüphanemizi tanımlıyoruz.
#include <MFRC522.h>     
int RST_PIN = 9;                          //RC522 modülü reset pinini tanımlıyoruz.
int SS_PIN = 10;   
MFRC522 rfid(SS_PIN, RST_PIN);            //RC522 modülü ayarlarını yapıyoruz.
byte ID[4] = {145, 90, 212, 38};          //Yetkili kart ID'sini tanımlıyoruz. 
byte ID2[4] = {243, 98, 199, 22};  
bool yetkili=0;


//------plaka
#define up 2
#define down 5
#define left 6
#define right 7
#define enter 8
bool upval=0;
bool downval=0;
bool leftval=0;
bool rightval=0;
bool enterval=0;
char Letters[34]={"ABCDEFGHIJKLMNOPRSTUVYZ 1234567890"};
char plaka[11]="";
int plaka_position=0;
int letter_position=0;

//record
#include <EEPROM.h>
int address = 0;
byte value;
//-----eeprom val
//150,160 long sum dist
//0-11 plaka
//100,101,102 ref year




//--Geçerlilik süresi----
unsigned long refyymmdd;
char urunKodu[11]="1111111111";
int urunKodu_position=0;


//*****************************************************
//****************************************************


void setup()
{  
  Serial.begin(115200);  
  ss.begin(9600);
  pinMode(sensorpin,INPUT);

  //---plaka
  pinMode(up,INPUT);
  pinMode(down,INPUT);
  pinMode(left,INPUT);
  pinMode(right,INPUT);
  pinMode(enter,INPUT);
  for (int i=0;i<10;i++){
    plaka[i] = EEPROM.read(i);
    }  

      

  //opening screen
  u8g.firstPage();
    do {
      draw1();
    } while (u8g.nextPage() );
    delay(2000);
    
    
//----yetkilendirme 
  SPI.begin(); 
  rfid.PCD_Init(); 
  
    
  while(1){
    u8g.firstPage();
      do {
        draw2();
      } while (u8g.nextPage() );
      delay(100);
          
    authorization();
    if(yetkili==1) break;
  }

   yetkili=0; // inorder to unauthorize

  //--plakagirilmesi
  while(1){
    plakaGir();
    if (enterval==1) break;
    
  }
  
  //---geçerlilik süresi
  int yy=EEPROM.read(100);
  int mm=EEPROM.read(101);
  int dd=EEPROM.read(102);
  refyymmdd=long(yy)*10000+long(mm)*100+dd;
  Serial.print("refyymmdd:  ");Serial.println(refyymmdd);

  //reading distances from eeprom
  EEPROM.get(150,sum_distance1);
  EEPROM.get(160,sum_distance2); 
  
  

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

//******************************************************
//******************************************************

void loop()
{
  Serial.println("--------------------");

  //GPS informations 
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
  int intspd=spd;
  Serial.print("spd "); Serial.println(spd);

  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age2;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age2);
  hour+=3;if(hour>=24)hour-=24;

//gps get date time

  unsigned long date, time;
  gps.get_datetime(&date, &time, &age);
  Serial.print("Date(ddmmyy): "); Serial.print(date); Serial.print(" Time(hhmmsscc): ");
  Serial.print(time);
  Serial.print(" Fix age: "); Serial.print(age); Serial.println("ms.");
//CheckDate
  checkDate(date);

  

  //-----------------------------------------------------------------

  // sensordeğeri okuma
  sensor=analogRead(sensorpin);
  Serial.print("sensor: "); Serial.println(sensor);

  
 
  //distance measurement
  currentMillis=millis();
  if(currentMillis - previousMillis >= 10000){
    distance = TinyGPS::distance_between(flat, flon, slat, slon);
    if (distance>250 || distance<0 ) distance=0; //set distance 0 if measure larger
    
    if(distance>30){
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
      u8g.setPrintPos(0, 64);
      u8g.print(sat);
      u8g.setPrintPos(64, 64);
      u8g.print(distance);
      
      
      u8g.setPrintPos(0, 10);
      if(hour<10) u8g.print("0"+String(hour));
      else u8g.print(hour);
      u8g.setPrintPos(10, 10);
      u8g.print(":");
      u8g.setPrintPos(16, 10);
      if(minute<10) u8g.print("0"+String(minute));
      else u8g.print(minute);

      
      u8g.setDefaultForegroundColor();
      u8g.drawBox(60, 0, 64, 11);      
      u8g.setDefaultBackgroundColor();
      u8g.setPrintPos(64, 10);
      u8g.print(plaka);
      u8g.setDefaultForegroundColor();  

   
      
      u8g.setPrintPos(0, 25);
      u8g.print("Bos:"); u8g.print(sum_distance1/1000);
      u8g.setPrintPos(64, 25);
      u8g.print("Yol:"); u8g.print(sum_distance2/1000);
      if (sensor>350){
        u8g.setPrintPos(120, 25);
        u8g.print("+");
        }

        
      //hız
      u8g.drawFrame(0,29,60,14);
     
      u8g.setPrintPos(4, 40);
      u8g.print("HIZ: ");
      u8g.print(intspd);
      
//sil sum distance
      u8g.setPrintPos(84, 40);
      u8g.print(sum_distance1);
      ;

    //sensör verisi
      u8g.setPrintPos(64, 55);
      u8g.print("s_val: ");
      u8g.print(sensor);
    
      
    } while (u8g.nextPage() );
    delay(10);


    //KM sıfırlama
  zeroizeDistance();

  //Save Distance

  unsigned long previousMillis3 = millis();
  if ((millis()-previousMillis3)>300000) saveDistance();  
  
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


void authorization(){

   if ( ! rfid.PICC_IsNewCardPresent()){    //Yeni kartın okunmasını bekliyoruz.
   
     delay(200);
    return;
  }
  if ( ! rfid.PICC_ReadCardSerial())      //Kart okunmadığı zaman bekliyoruz.
    return;

  if ((rfid.uid.uidByte[0] == ID[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) ||
   (rfid.uid.uidByte[0] == ID2[0] &&     //Okunan kart ID'si ile ID değişkenini karşılaştırıyoruz.
    rfid.uid.uidByte[1] == ID2[1] && 
    rfid.uid.uidByte[2] == ID2[2] && 
    rfid.uid.uidByte[3] == ID2[3] ) ){
        Serial.println("cihaz acilıyor...");
        ekranaYazdir();
        yetkili=1;

    }
    else{                                 //Yetkisiz girişte içerideki komutlar çalıştırılır.
      Serial.println("Yetkisiz Kart");
      ekranaYazdir();
      yetkili=0;
      
      u8g.firstPage();
      do {
        drawYetkisizKart();
      } while( u8g.nextPage() );
      delay(1500);
    }
  rfid.PICC_HaltA();
  
}

void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
  
}

//-----draw section-----------------------

void draw1(void){
  
    u8g.setFont(u8g_font_profont12);
    u8g.setPrintPos(0, 10);
    u8g.print("Mesafe Olcer");         
    u8g.setPrintPos(0, 25);
    u8g.print("v4");      
    u8g.setPrintPos(0, 40); 
  
}

void draw2(void){
    u8g.setFont(u8g_font_profont12);
    u8g.setPrintPos(0, 10);
    u8g.print("Lutfen Yetki Kartini");         
    u8g.setPrintPos(0, 25);
    u8g.print("Okutunuz!");      
    u8g.setPrintPos(0, 40); 
  
}

void drawYetkisizKart(void){
    u8g.setFont(u8g_font_profont12);
    u8g.setPrintPos(0, 10);
    u8g.print("!!!Gecersiz kart!!!");         
    u8g.setPrintPos(0, 25);
    u8g.print("Lutfen Yetkili Karti");      
    u8g.setPrintPos(0, 40); 
    u8g.print("Okutun!");  
  
}



//----------------------

void plakaGir(){
   upval=digitalRead(up);
   downval=digitalRead(down);
   leftval=digitalRead(left);
   rightval=digitalRead(right);  
   enterval=digitalRead(enter);

/*
  Serial.println("---------");
  Serial.print("up: ");Serial.println(upval);
  Serial.print("down: ");Serial.println(downval);
  Serial.print("left: ");Serial.println(leftval);
  Serial.print("right: ");Serial.println(rightval);
  Serial.print("enter: ");Serial.println(enterval);
  Serial.print("plaka: ");Serial.println(plaka);
  Serial.print("plaka_position: ");Serial.println(plaka_position);
  Serial.print("letter_position: ");Serial.println(letter_position);
  Serial.print("letter: ");Serial.println(Letters[letter_position]);
*/
  
  if( upval==1){
    letter_position++;
    if(letter_position>33)letter_position=0;
    plaka[plaka_position]=Letters[letter_position];
    EEPROM.update(plaka_position,Letters[letter_position]);
   }
  if(downval==1){
    letter_position--;
    if(letter_position<0)letter_position=33;
    plaka[plaka_position]=Letters[letter_position];
    EEPROM.update(plaka_position,Letters[letter_position]);
   }
  
  
  

  if( rightval==1){
     plaka_position++;
     if(plaka_position>9)plaka_position=0;
     for (int i=0; i<35; i++) {
     if (plaka[plaka_position] == Letters[i]) {
       letter_position = i;       
       break;
     }
     }
  }
  if(leftval==1){
    plaka_position--;
    if(plaka_position<0)plaka_position=9;
    for (int i=0; i<35; i++) {
    if (plaka[plaka_position] == Letters[i]) {
     letter_position = i;       
     break;
    }
    }
  }
   //print oled
  u8g.firstPage();
  do {
      uint8_t i, h;
      u8g_uint_t w, d;
    
      u8g.setFont(u8g_font_6x13);
      u8g.setFontRefHeightText();
      u8g.setFontPosTop();
      h = u8g.getFontAscent()-u8g.getFontDescent();
      w = u8g.getWidth();
      
       
      u8g.setPrintPos(0, 10);
      u8g.print("Plakayi Giriniz");         
      u8g.setPrintPos(0, 25);
      for (  i = 0; i < 10; i++ ) {
        u8g.setDefaultForegroundColor();
        if ( i == plaka_position ) {
          u8g.drawBox(i*6, 25, 6, h);
          u8g.setDefaultBackgroundColor();
        }
        u8g.print(plaka[i]);   
      }
      u8g.setDefaultForegroundColor();  
      u8g.setPrintPos(plaka_position*6, 40); 
      u8g.print(Letters[letter_position]);
    } 
    
    while (u8g.nextPage() );
  delay(50);
   
}

void checkDate(unsigned long date){
    
   long reverseDate= date/10000;   // dd
   reverseDate += (date/100) % 100*100;  // mm 
   reverseDate += (date % 100) *10000; // yy
   
    if (reverseDate>refyymmdd){
      uptadeDate();
      return;
    }
}

void uptadeDate(){

  
  while(1){
    upval=digitalRead(up);
    downval=digitalRead(down);
    leftval=digitalRead(left);
    rightval=digitalRead(right);  
    enterval=digitalRead(enter);


  if( upval==1){
    letter_position++;
    if(letter_position>33)letter_position=0;
    urunKodu[urunKodu_position]=Letters[letter_position];
    
   }
  if(downval==1){
    letter_position--;
    if(letter_position<0)letter_position=33;
    urunKodu[urunKodu_position]=Letters[letter_position];
   
   }
  
  
  

  if( rightval==1){
     urunKodu_position++;
     if(urunKodu_position>9)urunKodu_position=0;
     for (int i=0; i<35; i++) {
     if (urunKodu[urunKodu_position] == Letters[i]) {
       letter_position = i;       
       break;
     }
     }
  }
  if(leftval==1){
    urunKodu_position--;
    if(urunKodu_position<0)urunKodu_position=9;
    for (int i=0; i<35; i++) {
    if (urunKodu[urunKodu_position] == Letters[i]) {
     letter_position = i;       
     break;
    }
    }
  }
   //print oled
  u8g.firstPage();
  do {
      uint8_t i, h;
      u8g_uint_t w, d;
    
      u8g.setFont(u8g_font_6x13);
      u8g.setFontRefHeightText();
      u8g.setFontPosTop();
      h = u8g.getFontAscent()-u8g.getFontDescent();
      w = u8g.getWidth();
      
       
      u8g.setPrintPos(0, 10);
      u8g.print("Kullanim Suresi doldu");
      u8g.setPrintPos(0, 25);
      u8g.print("Lutfen Kodu Giriniz"); 
              
      u8g.setPrintPos(0, 40);
      for (  i = 0; i < 10; i++ ) {
        u8g.setDefaultForegroundColor();
        if ( i == urunKodu_position ) {
          u8g.drawBox(i*6, 40, 6, h);
          u8g.setDefaultBackgroundColor();
        }
        u8g.print(urunKodu[i]);   
      }
      u8g.setDefaultForegroundColor();  
      u8g.setPrintPos(urunKodu_position*6, 55); 
      u8g.print(Letters[letter_position]);
    } 
    
    while (u8g.nextPage() );
    delay(10);

    Serial.print("urunkodu");Serial.println(urunKodu);



  
    if(enterval==1){
        if(String(urunKodu)=="2111111111"){
          refyymmdd=240625;
          EEPROM.put(100,24);
          EEPROM.put(101,06);
          EEPROM.put(102,25);
          
          Serial.println("Dogru kod girildi");
          return;
        }
         if(String(urunKodu)=="311111111"){
          refyymmdd=250626;
          EEPROM.put(100,25);
          EEPROM.put(101,06);
          EEPROM.put(102,26);
          Serial.println("Dogru kod girildi");
          return;
        }
         if(String(urunKodu)=="411111111"){
           refyymmdd=260627;
           EEPROM.put(100,26);
           EEPROM.put(101,06);
           EEPROM.put(102,27);
           Serial.println("Dogru kod girildi");
           return;
        }

        
     }
 
  }
    
}


void zeroizeDistance(){
    enterval=digitalRead(enter);
    if (enterval==1){
      u8g.firstPage();
      do {
        draw2();
        } while (u8g.nextPage() );
      delay(100);

      unsigned long previousMillis2 = millis();
      while(millis()-previousMillis2<10000){ //after 10 sec exit this mode
        authorization();        
        if (yetkili==1){
          sum_distance1=0;
          sum_distance2=0;
          break;
        }        
      }          
    }


  
}

void saveDistance(){
  unsigned long sum_distance1_v2;
  unsigned long sum_distance2_v2;
  EEPROM.get(150,sum_distance1_v2);
  EEPROM.get(160,sum_distance2_v2);

  //to protect eeprom lifecycle write values if only they changes.
  //EEPROM.update is not working cuz they are long.
  if (sum_distance1>sum_distance1_v2) EEPROM.put(150,sum_distance1);
  if (sum_distance1>sum_distance2_v2) EEPROM.put(160,sum_distance2);
  
}












  
