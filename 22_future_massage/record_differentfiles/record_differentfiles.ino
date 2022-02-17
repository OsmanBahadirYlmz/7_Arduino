/*
Steps:
1. Edit pcmConfig.h
    a: On Uno or non-mega boards, #define buffSize 128. May need to increase.
    b: Uncomment #define ENABLE_RECORDING and #define BLOCK_COUNT 10000UL

2. Usage is as below. See https://github.com/TMRh20/TMRpcm/wiki/Advanced-Features#wiki-recording-audio for
   additional informaiton.
*/

#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>
#define SD_ChipSelectPin 10
TMRpcm audio;

 //button definition
 bool recmode = 0;
 int audiofile = 0;
 unsigned long i = 0; 

#define hookpin 2;
//fordifferent files

uint32_t myFileNumber = (analogRead(A0)*1000);
char audioFilename[13];

bool flag=0;


void setup() {
  pinMode(A0, INPUT);
  pinMode(4, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  audio.speakerPin = 9;
  
  SD.begin(SD_ChipSelectPin);
  audio.CSPin = SD_ChipSelectPin;
  Serial.begin(9600);
  
  while (!SD.begin(SD_ChipSelectPin)) { 
    Serial.println("SD okunamadı"); 
    
 }
  Serial.println("SD OK");   
  Serial.println("kayıt baslıyor");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);
  Serial.println("kayıt");



  audio.startRecording("b1.wav", 16000, A0);
  delay(2000);
  audio.stopRecording("b1.wav"); 
  Serial.println("kayıt ok"); 
  audio.play("b1.wav");
  Serial.println("play");


 //attachInterrupt(digitalPinToInterrupt(2), button, HIGH);

}

void button() {
// while (i < 300000) {
//    i++;
//  }
//  i = 0;
//
//if (recmode == 0) {
//    digitalWrite(4, HIGH);
//    recmode = 1;
//    myFileNumber++;
//    Serial.print("kayıt");Serial.println(myFileNumber);
//   
//    audio.startRecording(snprintf(filename, 12, "%08d.WAV", myFileNumber) , 16000, A0);
//}
//
// else {
//    recmode = 0;
//    digitalWrite(4, LOW);
//     Serial.print("stop");
//    audio.stopRecording(snprintf(filename, 12, "%08d.WAV", myFileNumber));
//    
// }
//


  
}


void loop() {


//audio record and stop
flag=digitalRead(2);
Serial.println(flag);

//used 2 parameter one for check hook is pressed the other we re recordin or stopping phase
if (flag && !recmode ) {
    digitalWrite(4, HIGH);
    recmode = 1;
    myFileNumber++;     
    itoa(myFileNumber,audioFilename,10);//continous file record
    strcat(audioFilename, ".wav");
    Serial.println("kayıt");Serial.println(audioFilename);   
    audio.startRecording( audioFilename, 16000, A0);
}

 if (!flag && recmode) {
    recmode = 0;
    digitalWrite(4, LOW);
     Serial.print("stop");
    audio.stopRecording(audioFilename);
    audio.play(audioFilename);
    
 }

  

delay(1000);
}
