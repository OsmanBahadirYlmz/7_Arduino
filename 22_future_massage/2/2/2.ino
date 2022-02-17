#include <SD.h>               // need to include the SD library
#define SD_ChipSelectPin 10   //pin10 for Arduino Pro Mini
#include <TMRpcm.h>           //  Lib to play wav file
#include <SPI.h>

TMRpcm tmrpcm;   // create an object for use in this sketch


void setup(){
  tmrpcm.speakerPin = 9; //pin 9 for Aduino Pro Mini , any pin with PWM fonction will work too
  Serial.begin(9600);

  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  else{   
    Serial.println("SD ok");   
  }
  
  tmrpcm.volume(2); //default volume to 2 
}

void loop(){
 tmrpcm.play("music.wav");
delay(4000);

  
}
