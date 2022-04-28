#define yesilled 5
#define sariled 6
#define kirmiziled 7

#define button1 2
#define button2 3
#define button3 4


int motorpin1 = 9;
int motorpin2 = 10;
int hiz=125;
bool yon=1 ;

//çift tik sayıcı

int buttonState;
unsigned long timePress = 0;
unsigned long timePressLimit = 0;
int clicks = 0;



void setup() {
  Serial.begin(9600);
  
   pinMode(yesilled,OUTPUT);
   pinMode(sariled,OUTPUT);
   pinMode(kirmiziled,OUTPUT);

   pinMode(button1,INPUT);

   
   pinMode(button2,INPUT);
   pinMode(button3,INPUT);
  
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);

}

void motorgeri(){

  analogWrite(motorpin1,hiz);
  analogWrite(motorpin2,LOW);
  
}

void motorileri(){

  analogWrite(motorpin1,LOW);
  analogWrite(motorpin2,hiz);
  
}



void loop() {
  Serial.print(hiz);Serial.print("---");Serial.println(yon);
  if (digitalRead(button3)==1){
    hiz+=25;
    delay(300);
      }

  if (digitalRead(button2)==1){
    hiz-=25;
    delay(300);
      }



  if(hiz<=50){
    digitalWrite(yesilled,HIGH);
    digitalWrite(sariled,HIGH);
    digitalWrite(kirmiziled,HIGH);
    delay(20);
    digitalWrite(kirmiziled,LOW);
    delay(40);
  }
  if (hiz<0){
    hiz=0;
 
  }
  if (hiz>=250) {
    hiz=250;
    digitalWrite(yesilled,HIGH);
    digitalWrite(sariled,HIGH);
    digitalWrite(kirmiziled,HIGH);
    delay(20);
    digitalWrite(kirmiziled,LOW);
    delay(40);
    
  }

//çift tık algılayıcı
  buttonState = digitalRead(button1);
  
  if (buttonState == HIGH){
    delay(200);
    Serial.println("Button Pressed");
    
    if (clicks == 0) {
    timePress = millis();
    timePressLimit = timePress + 1000;    
    clicks = 1;
    }

    else if (clicks == 1 && millis() < timePressLimit){
      Serial.println("Button Pressed twice");
     
     //2 tıkta yapılacakalar
     if (hiz == 0)yon=0;    

     //set variables back to 0
      timePress = 0;
      timePressLimit = 0;
      clicks = 0;      
    }    
  }

  if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit){
     Serial.println("Button Pressed Once");
     timePress = 0;
     timePressLimit = 0;
     clicks = 0;

     //tek tıkta yapılacaklar
     if (hiz == 0)yon=1;
     else yon=!yon;
     

    }




  
  if(yon==1) motorileri();
  if(yon==0) motorgeri();
  
//led koşulları
  if( hiz<51 && hiz>0) {
    digitalWrite(yesilled,LOW);
    digitalWrite(kirmiziled,HIGH);
  }

  if( hiz<250 && hiz>199){
    digitalWrite(yesilled,LOW);
    digitalWrite(kirmiziled,HIGH);
    
    }
  
  if( hiz<200 && hiz>50){
    digitalWrite(yesilled,HIGH);
    digitalWrite(kirmiziled,LOW);
    
    }
    

  
  if( yon==1)digitalWrite(sariled,LOW);
  if( yon==0)digitalWrite(sariled,HIGH);
  

}
