//ilgili kütüphanene
#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;


//mesafe modülü
#define echoPin 9 //  HC-SR04 sensörünün echo pinini d9 a bağla
#define trigPin 10 // HC-SR04 sensörünü trig pinini d10 a bağla
long zaman;
int mesafe;

#define buzzer 11
#define yesilled 2
#define sariled 3
#define kirmiziled 4


void setup() {
   lcd.begin(16, 2);
 

   pinMode(trigPin,OUTPUT);
   pinMode(echoPin,INPUT);

   pinMode(buzzer,OUTPUT);
   pinMode(yesilled,OUTPUT);
   pinMode(sariled,OUTPUT);
   pinMode(kirmiziled,OUTPUT);
}

void loop() {
//mesafe hesaplaması ve ekrana yazılması
    digitalWrite(trigPin, LOW); //trigpin low yapıyoruz
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); //ardından 10 ms on yapıyoruz
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // echo pinini okuyup ses dalgasının gidip gelme süresini oku
    zaman = pulseIn(echoPin, HIGH);
    // mesafe hesaplanıyor
    mesafe = zaman * 0.034 / 2; //  git gel süresi olduğu için 2 ye bölüyoruz
    // mesafeyi lcdye yazdırma
    lcd.clear();
    lcd.print("MESAFE");
    lcd.setCursor(5,1);
    lcd.print(mesafe);lcd.print(" cm");



//ledlerin yakılması 

  //koşul 1
    if(mesafe>50 && mesafe<100){
      digitalWrite(yesilled,HIGH);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(yesilled,LOW);
      digitalWrite(buzzer,LOW);
      delay(100); 

      digitalWrite(kirmiziled,LOW);//10 cm den yakın olunca yanan kırmızıyı söndürmek için
    }

  //koşul 2
    if(mesafe>25 && mesafe<51){
      digitalWrite(sariled,HIGH);
      digitalWrite(buzzer,HIGH);
      delay(50);
      digitalWrite(sariled,LOW);
      digitalWrite(buzzer,LOW);
      delay(50);  

      digitalWrite(kirmiziled,LOW);//10 cm den yakın olunca yanan kırmızıyı söndürmek için    
    }

  //koşul 3
    if(mesafe>10 && mesafe<26){
      digitalWrite(kirmiziled,HIGH);
      digitalWrite(buzzer,HIGH);
      delay(10);
      digitalWrite(kirmiziled,LOW);
      digitalWrite(buzzer,LOW);
      delay(10);      
    }
    

  //koşul 4
    if(mesafe<=10){
      digitalWrite(kirmiziled,HIGH);
      digitalWrite(buzzer,HIGH);


      
      digitalWrite(sariled,HIGH);
      digitalWrite(yesilled,HIGH);
      delay(50);    
      digitalWrite(sariled,LOW);
      digitalWrite(yesilled,LOW);
      delay(50);
       
    }

  //herhangi diğer koşula girmeyen durumda tüm uyarıların kapatılması
    if(mesafe>100){
      
      digitalWrite(sariled,LOW);
      digitalWrite(yesilled,LOW);
      digitalWrite(kirmiziled,LOW);
      digitalWrite(buzzer,LOW);
      
    }



}
