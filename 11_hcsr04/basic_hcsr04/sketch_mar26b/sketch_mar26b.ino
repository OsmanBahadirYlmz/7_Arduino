
#define trigPin 6
#define echoPin 5
long duration;
int distance;
void setup() {
   pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
   Serial.begin(9600);

}

void loop() {
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
  delay(1000);
}
