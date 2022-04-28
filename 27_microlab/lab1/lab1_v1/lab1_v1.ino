
//ledlere ait pin tanımları
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define led5 5
#define led6 6
#define led7 7
#define led8 8

//buttonlara ait pin tanımları
#define b1pin 10
#define b2pin 11
#define b3pin 12
#define b4pin 13
#define b5pin A5
#define b6pin A4
#define b7pin A3
#define b8pin A2
#define b9pin A1

//buttonlara ait durum değişkenleri
int b1=0;
int b2=0;
int b3=0;
int b4=0;
int b5=0;
int b6=0;
int b7=0;
int b8=0;
int b9=0;

const int buzzer = 9; //buzzer arduinonun 9. pinine bağlandı


//kullanılan global değişkenler

int b1sayici=0; //2.soru için gerelli değişken, b1 e kaç defa basıldığını sayıyor
int b7sayici=0; //8.soru için gerelli değişken, b7 e kaç defa basıldığını sayıyor






void setup() {


  //ledler çıkış olarak tanımlanır
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT);

  //buttonlar giriş olarak tanımlanır
  pinMode(b1pin,INPUT);
  pinMode(b2pin,INPUT);
  pinMode(b3pin,INPUT);
  pinMode(b4pin,INPUT);
  pinMode(b5pin,INPUT);
  pinMode(b6pin,INPUT);
  pinMode(b7pin,INPUT);
  pinMode(b8pin,INPUT);
  pinMode(b9pin,INPUT);

  pinMode(buzzer, OUTPUT); // buzzer pini output olarak ayarlandı


  
}

void loop() {

//2.soru - 1. buttona 3 defa basinca tüm ledler sönecek
if (digitalRead(b1pin)==HIGH){
  b1sayici++ ;                //buttona her basıldığında sayaç 1 artıyor
  if (b1sayici==3){          //button sayıcı 3 olduğunda led yanıyor ve sayaç sıfırlanıyor
    b1sayici=0;
    digitalWrite(led1,HIGH);
    
  }
  while(digitalRead(b1pin))delay(10); //buttona basılı kaldığı sürüce bekleyecek

}


//3.soru

if (digitalRead(b2pin)==HIGH){
  while(digitalRead(b2pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek
  
  for (int i=0;i<9;i++){              //tüm ledler sönecek
  digitalWrite(i,LOW);
  }
  delay(500);
  for (int i=0;i<9;i++){            //tüm ledler sırayla yanıyor
  digitalWrite(i,HIGH);
  delay(500);
  }

  
}




//4. soru

if (digitalRead(b3pin)==HIGH){
  while(digitalRead(b3pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek
  
  for (int i=0;i<9;i++){              //tüm ledler sönecek
    digitalWrite(i,LOW);
  }
  delay(500);
  for (int i=8;i>0;i--){            //tüm ledler sırayla yanıyor
    digitalWrite(i,HIGH);
    delay(500);
  }

  
}

//5.soru
if (digitalRead(b4pin)==HIGH){
  while(digitalRead(b4pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek
  
  for (int i=0;i<9;i++){              //tüm ledler sönecek
    digitalWrite(i,LOW);
  }
  delay(100);

  for(int i=0;i<256;i++){
    if ((i%2)>0) digitalWrite(led1,HIGH); else digitalWrite(led1,LOW); 
    if ((i%4)>1)  digitalWrite(led2,HIGH); else digitalWrite(led2,LOW); 
    if ((i%8)>3)  digitalWrite(led3,HIGH); else digitalWrite(led3,LOW); 
    if ((i%16)>7)  digitalWrite(led4,HIGH); else digitalWrite(led4,LOW);
    if ((i%32)>15) digitalWrite(led5,HIGH); else digitalWrite(led5,LOW); 
    if ((i%64)>31)  digitalWrite(led6,HIGH); else digitalWrite(led6,LOW); 
    if ((i%128)>63)  digitalWrite(led7,HIGH); else digitalWrite(led7,LOW); 
    if ((i%256)>127)  digitalWrite(led8,HIGH); else digitalWrite(led8,LOW); 
    delay(75);
  }
  
  }

//6.soru
if (digitalRead(b5pin)==HIGH){
  while(digitalRead(b5pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek
  
  for (int i=0;i<9;i++){              //tüm ledler sönecek
    digitalWrite(i,LOW);
  }
  delay(500);

  for (int i=1;i<9;i+=2){              //1-3-5-7. ledler yanacak
    digitalWrite(i,HIGH);
  }
}


//7.soru

if (digitalRead(b6pin)==HIGH){
  while(digitalRead(b6pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek
  
  for (int i=0;i<9;i++){              //tüm ledler sönecek
    digitalWrite(i,LOW);
  }
  delay(500);

  for (int i=0;i<9;i+=2){              //2-4-6-8. ledler yanaca
    digitalWrite(i,HIGH);
  }
}

//8.soru

if (digitalRead(b7pin)==HIGH){
 
  b7sayici++;
  if(b7sayici==9) b7sayici=1;      //b7sayici 9 olduğunda başa dönecek
  while(digitalRead(b7pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek

 
  for (int i=0;i<9;i++){              //tüm ledler sönecek
  digitalWrite(i,LOW);
    
   
      
  }

   digitalWrite(b7sayici,HIGH);  // b7sayici kaçsa ilgili led yanacak
   delay(100);
    

    
  }
  
//9.soru 
if (digitalRead(b8pin)==HIGH){
  while(digitalRead(b8pin))delay(10);   //buttona basılı kaldığı sürüce bekleyecek
  
  for (int i=0;i<9;i++){              //tüm ledler sönecek
    digitalWrite(i,LOW);
  }
  digitalWrite(buzzer,HIGH);  //buzzer 2 saniye ötecek
  delay(2000);
  digitalWrite(buzzer,LOW);

}


}
 
