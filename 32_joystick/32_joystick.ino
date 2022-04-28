#include "U8glib.h"
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);

#define xway 2
#define yway 3
#define sw 11

int xval;
int yval;
int swval;

char Letters[34]={"ABCDEFGHIJKLMNOPRSTUVYZ 1234567890"};
char plaka[10]="10 KB 776";
int plaka_position=0;
int letter_position=0;


void setup() {
  Serial.begin(9600);
  pinMode(xway, INPUT);
  pinMode(yway, INPUT);
  pinMode(sw, INPUT);
  for(int i=0;i<35;i++){
    Serial.print(i);Serial.println(Letters[i]);
  }

}



void loop() {
  xval=analogRead(xway);
  yval=analogRead(yway);
  swval=digitalRead(sw);
  Serial.print("*********************: ");Serial.println(digitalRead(sw));
  
  Serial.println("---------");
  Serial.print("xwal: ");Serial.println(xval);
  Serial.print("ywal: ");Serial.println(yval);
  Serial.print("sw: ");Serial.println(swval);
  Serial.print("plaka: ");Serial.println(plaka);
  Serial.print("plaka_position: ");Serial.println(plaka_position);
  Serial.print("letter_position: ");Serial.println(letter_position);
  Serial.print("letter: ");Serial.println(Letters[letter_position]);

  if( yval<200) letter_position++;
  if(yval>650) letter_position--;
  if(letter_position<0)letter_position=33;
  if(letter_position>33)letter_position=0;
  

  if( xval<200) plaka_position++;
  if(xval>650) plaka_position--;
  if(plaka_position<0)plaka_position=9;
  if(plaka_position>9)plaka_position=0;

  if(swval==1) plaka[plaka_position]=Letters[letter_position];

  u8g.firstPage();
  do {
      u8g.setFont(u8g_font_profont12);
      u8g.setPrintPos(0, 10);
      u8g.print("Plakayi Giriniz");         
      u8g.setPrintPos(0, 25);
      u8g.print(plaka);      
      u8g.setPrintPos(plaka_position*6, 40); 
      u8g.print(Letters[letter_position]);  
      

    } while (u8g.nextPage() );
  delay(50);

   
  
  
}
