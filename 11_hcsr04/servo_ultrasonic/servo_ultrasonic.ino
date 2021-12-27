#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

long duration;
int distance;
int pdistance;
int position=0;

#include<Servo.h>
Servo Myservo;

void setup(){
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    Serial.begin(9600);
    Myservo.attach(5);


}

void loop(){
    // Clears the trigPin condition
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    //Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    
     if (distance<100) position=map(distance,0,100,0,180);
     else position+=1;

   
    Myservo.write(position);
    Serial.print("position");Serial.println(position);

    pdistance=distance;


    delay(30);
}
