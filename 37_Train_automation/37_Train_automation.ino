#define echoPin 7 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 8 //attach pin D3 Arduino to pin Trig of HC-SR04
long duration;
int distance;

//potantiometer pin for motor speed
#define potpin A0
float pot=0;

//button defination
#define buton1 2
#define buton2 3
bool valButon1=0;
bool valButon2=0;
bool start=0;
bool goForward=1;


//buzzer defination
const int buzzer1 = 11; //buzzer to arduino pin 9

#define led 4 //led defination

//motor defination
int motor1pin1 = 5;
int motor1pin2 = 6;

int motor2pin1 = 9;
int motor2pin2 = 10;




void setup() {
    Serial.begin(9600);
    Serial.println("Setup");
  
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    Serial.begin(9600);

    pinMode(potpin,INPUT);

    pinMode(buton1,INPUT);
    pinMode(buton2,INPUT);

    pinMode(buzzer1, OUTPUT);

    pinMode(led, OUTPUT);

    pinMode(motor1pin1, OUTPUT);
    pinMode(motor1pin2, OUTPUT);
    pinMode(motor2pin1, OUTPUT);
    pinMode(motor2pin2, OUTPUT);
  
}

void measureDistance(){
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
  delay(10);
  if (distance<25) {
    stopTrain();
    waitStation();
  }
  
  
}

void buzzer(){
  Serial.println("buzzerON");
  for(int i=0;i<4;i++){
    tone(buzzer, 500);
    delay(200);
    noTone(buzzer);
    delay(200);
  }
  tone(buzzer, 500);
  delay(800);
  noTone(buzzer);
  delay(10);
  
}

void forward(){
  Serial.println("Forward");
  analogWrite(motor1pin1,pot);
  analogWrite(motor1pin2,0);
  
  analogWrite(motor2pin1,pot);
  analogWrite(motor2pin2,0);

  digitalWrite(led,HIGH);
  
}

void backward(){
  Serial.println("Backward");
  analogWrite(motor1pin1,0);
  analogWrite(motor1pin2,pot);
  
  analogWrite(motor2pin1,0);
  analogWrite(motor2pin2,pot); 
  
  digitalWrite(led,HIGH); 
}

void stopTrain(){
  Serial.println("STOP");
  analogWrite(motor1pin1,255);
  analogWrite(motor1pin2,255);
  
  analogWrite(motor2pin1,255);
  analogWrite(motor2pin2,255);
  delay(1500);
  analogWrite(motor1pin1,0);
  analogWrite(motor1pin2,0);
  
  analogWrite(motor2pin1,0);
  analogWrite(motor2pin2,0);
  
  digitalWrite(led,LOW);
    
}

void waitStation(){
  Serial.println("waitStation");
  delay(15000);
  buzzer();
  delay(2000);
  buttonRead();

  //move away slowly from station
  pot=70;
  trainAction();
  delay(5000);
  
    
}

void buttonRead(){
  valButon1=digitalRead(buton1);
  valButon2=digitalRead(buton2); 
  if(digitalRead(buton1)==HIGH){
    start=!start;
    while(digitalRead(buton1))delay(20);
  }
  
  if(digitalRead(buton2)==HIGH){
    goForward=!goForward;
    while(digitalRead(buton2))delay(20);
   }
}

void trainAction(){
  if(start==1 && goForward==1){
    forward();    
  }
  if(start==1 && goForward==0){
    backward();    
  }

  if(start==0) stopTrain();
  delay(10);  
  
  
}


void loop() {
  measureDistance();
  
//Read potantiometer  
  pot=analogRead(potpin)*5/1024;
  Serial.print("pot value"); Serial.println(pot);


  
//Read button position
  buttonRead();
 

//move conditions
  trainAction();
  

}
