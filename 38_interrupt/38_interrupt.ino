
const byte interruptPin1 = 2;
const byte interruptPin2 = 3;

volatile byte state1 = LOW;
volatile byte state2 = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(interruptPin1, INPUT_PULLUP);
  pinMode(interruptPin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin1), blink, CHANGE);
  attachInterrupt(digitalPinToInterrupt(interruptPin2), blink2, CHANGE);

}

void loop() {
  Serial.println("loop");
  delay(1000);
}

void blink() {
  state1 = !state1;
  Serial.println("blink");
}

void blink2(){
  state2 = !state2;
  Serial.println("blink2");
}
