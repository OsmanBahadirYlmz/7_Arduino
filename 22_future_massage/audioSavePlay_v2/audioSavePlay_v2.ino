
#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#define SD_ChipSelectPin 10
TMRpcm audio;

 //button definition
 bool recmode = 0;
 int audiofile = 0;
 unsigned long i = 0; 



//record different files
uint32_t myFileNumber ;
char audioFilename[13];
bool flag=0;


//hcr04 distance sensor
#define trigPin 6
#define echoPin 5
#define hookpin 2 //flag=digitalread(hookpin)
long duration;
int distance;


//define electromagnet
#define magnet1 7
#define magnet2 8 
unsigned long previousMillis = 0;

//eeprom store to not overwrite
#include <EEPROM.h>
int address = 0;
byte value;



void setup() {
  pinMode(A0, INPUT);
  pinMode(4, OUTPUT);//record LED
  audio.speakerPin = 9;
  
  SD.begin(SD_ChipSelectPin);
  audio.CSPin = SD_ChipSelectPin;
  Serial.begin(9600);

//  myFileNumber=(analogRead(A0)*1000); //give random to file name
  
//hcr04 distance sensor
  pinMode(hookpin,INPUT);
  Serial.begin(9600);
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

//define elctromagnet
  pinMode(magnet1,OUTPUT);
  pinMode(magnet2,OUTPUT);

  
  
  while (!SD.begin(SD_ChipSelectPin)) { 
    Serial.println("SD okunamadı"); 
    
 }
  Serial.println("SD OK");

  //Test REC
  Serial.println("kayıt baslıyor");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("kayıt");



  audio.startRecording("test1.wav", 16000, A0);
  delay(2000);
  audio.stopRecording("test1.wav"); 
  Serial.println("kayıt ok"); 
  audio.play("test1.wav");
  Serial.println("play");

//EEPROM FOR not overwrite

value = EEPROM.read(address);
if(value>1) myFileNumber=value;




}



void loop() {


//audio record and stop
flag=digitalRead(hookpin);//hookpin
Serial.print("flag-hookpin: ");Serial.println(flag);

//used 2 parameter one for check hook is pressed the other we re recordin or stopping phase
if (flag && !recmode ) {
    audio.play("test1.wav"); //play user note
    delay(5000);
    digitalWrite(4, HIGH);
    recmode = 1;
    myFileNumber++;
    
    //EEPROM
    if(myFileNumber>30000) myFileNumber=1; //protect to overflow
    EEPROM.write(address, myFileNumber);
         
    itoa(myFileNumber,audioFilename,10);//continous file record
    strcat(audioFilename, ".wav");
    Serial.println("kayıt başladı,dosya ismi:");Serial.println(audioFilename);   
    audio.startRecording( audioFilename, 16000, A0);
}

 if (!flag && recmode) {
    recmode = 0;
    digitalWrite(4, LOW);
    Serial.print("kayıt durdu");
    audio.stopRecording(audioFilename);
    audio.play(audioFilename);
    delay(5000);
    
 }

//calculate distance
if(flag==0) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);    //Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("distance: ");Serial.println(distance);   
}

//ring phone

if(flag==0 && distance<150 && distance>10 &&   millis-previousMillis<3000){
  previousMillis=millis;
  
      for (int i=0; i<15;i++){
        if (flag) break; //stop if hook rises   
        digitalWrite(magnet1,HIGH);
        digitalWrite(magnet2,LOW);
        delay(100);
        digitalWrite(magnet1,LOW);
        digitalWrite(magnet2,HIGH);
        delay(100);
        }
  digitalWrite(magnet1,LOW);
  digitalWrite(magnet2,LOW);


}

  

delay(1000);
}
