int DOpin = 2;

void setup() {
Serial.begin(9600);
pinMode(DOpin, INPUT);
}

void loop() {
int DO = digitalRead(DOpin);
double sensorValue = analogRead(A0);
int hum = 100 -(sensorValue*100/1024);

Serial.print("Digital value: ");
Serial.println(DO);

Serial.print("Analog value: ");
Serial.println(sensorValue);

Serial.print("Humidity: ");
Serial.print(hum);
Serial.println("%");
delay(500); 
}
