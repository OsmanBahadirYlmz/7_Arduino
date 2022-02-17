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
int audiofile = 0;
unsigned long i = 0;
bool recmode = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(6, OUTPUT);
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



  audio.startRecording("r10.wav", 16000, A0);
  delay(10000);
  audio.stopRecording("r10.wav"); 
  Serial.println("kayıt ok"); 
  audio.play("r10.wav");
  Serial.println("play");
}
void loop() {
 
  

}
