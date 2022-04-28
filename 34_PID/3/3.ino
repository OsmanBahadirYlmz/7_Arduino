/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

#include <CheapStepper.h>
CheapStepper stepper;
boolean moveClockwise = true;



void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  float pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  float roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  // Output
  Serial.print(" Pitch = ");
  Serial.print(pitch,2);
  Serial.print(" Roll = ");
  Serial.println(roll,2);
  
  Serial.println(roll*11.37);


  if(roll>0){
    if(roll>5){
      for(int i=0;i<(roll*11);i++){
        Serial.println("----------------");
        Serial.println(i);
        stepper.step(moveClockwise);
      }
    }
    stepper.step(moveClockwise);
  }
  if(roll<0){
     if(roll<-5){
      for(int i=0;i<(roll*11*-1);i++){
        stepper.step(!moveClockwise);
      }
     }
    stepper.step(!moveClockwise);
  }

  
  
  delay(100);
}
