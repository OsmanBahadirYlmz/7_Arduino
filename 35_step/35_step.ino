#define in1 8
#define in2 9
#define in3 10
#define in4 11
int konum,bekleme;


void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
  konum=8;
  bekleme=10;
  
  

}

void loop() {
  digitalWrite(in1,HIGH

}

void solaDon (int adim){
  for (int i=0;i<adim;i++{
    digitalWrite(konum,HIGH);
    delay(bekleme);
    digitalWrite(konum,LOW);
    konumArttir();
  }
}


void sogaDon (int adim){
  for (int i=0;i<adim;i++{
    digitalWrite(konum,HIGH);
    delay(bekleme);
    digitalWrite(konum,LOW);
    konumAzalt();
  }
}

void konumArttir(){
  konum++;
  if(konum==12) konum=8;
  
}


void konumAzalt(){
  konum--;
  if(konum==7) konum=11;
  
}
