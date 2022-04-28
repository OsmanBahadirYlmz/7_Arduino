//ilgili kütüphanene
#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;


//butonlar tanımları
#define buton1 3
#define buton2 4
#define buton3 5

//yazılacak metinler 
String text1="KKU MMF EEM";
String text2="200204079 DEN 2";

//her bir satırı ortalayan değerler
int baslangic1=2 ; //1.satırı ortalı yapan değer
int baslangic2=0 ; //2.satırı ortalı yapan değer

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);

  //ortalı şekilde il
  lcd.setCursor(baslangic1,0); 
  lcd.print(text1);
  lcd.setCursor(baslangic2,1);
  lcd.print(text2);
  delay(1000);

}

void yaz(){
  
  lcd.clear();
  lcd.setCursor(baslangic1,0);
  lcd.print(text1);
  lcd.setCursor(baslangic2,1);
  lcd.print(text2);
  
}
void loop() {
Serial.print("bas1: ");Serial.println(baslangic1);
Serial.print("bas2: ");Serial.println(baslangic2);
  
  if(digitalRead(buton1)==1){
     baslangic1++;
     baslangic2++;
     yaz();     
     delay(400);
    }

  if(digitalRead(buton3)==1){
     baslangic1--;
     baslangic2--;
     yaz();
     delay(400);
    }
   if(digitalRead(buton2)==1){
     baslangic1=2;
     baslangic2=0;
     yaz();
     delay(400);
    }
    

    

  
}
