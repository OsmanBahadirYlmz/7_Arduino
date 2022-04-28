int motor1pin1 = 5;
int motor1pin2 = 6;
int pwm=0;

#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#include <PID_v1.h>
double Setpoint, Input, Output;
//Specify the links and initial tuning parameters
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);


void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

 Setpoint=0;
 myPID.SetMode(AUTOMATIC);
  Serial.print(" Pitch = ");
}

void loop() {


  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  float pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  float roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  // Output
  Serial.print(" Pitch = ");
  Serial.print(pitch,2);
  Serial.print(" Roll = ");
  Serial.print(roll,2);
  Serial.println();
  
  Input=roll;
  myPID.Compute();
  
  Serial.print("output: ");Serial.println(Output);
  

  if (roll<0){
    analogWrite(motor1pin1,Output);
    analogWrite(motor1pin2,0);
  }
  
  if (roll>0){
    analogWrite(motor1pin2,Output);
    analogWrite(motor1pin1,0);
  }


  
  delay(100);




  
}
