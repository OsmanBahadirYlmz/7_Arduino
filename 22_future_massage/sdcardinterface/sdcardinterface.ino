#define hookpin 2

#define trigPin 6
#define echoPin 5
long duration;
int distance;


int state=0;
void setup() {
  pinMode(hookpin,INPUT);
  Serial.begin(9600);
  
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

}

void loop() {
 state=digitalRead(hookpin);
 Serial.println(state);


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
  delay(200);


 

}
