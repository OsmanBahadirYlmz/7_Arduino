const int Pot1 = A0;   // Analog input pin that the potentiometer 1 is wired to
const int Pot2 = A1;   // Analog input pin that the potentiometer 2 is wired to
const int Led1 = 2;   // Digital pin that the LED 1 is wired to
const int Led2 = 13;   // Digital pin that the LED 2 is wired to
 
float Pot1_row_value = 0;  // raw value read from the pot1
float Pot2_row_value = 0;  // raw value read from the pot2 
 
void setup() {
  // initialize digital pins for led as an output.
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  // initialize serial communications at 9600 bps:

  
  Serial.begin(9600);
  Serial.println("a");
  char a="b";
  while (a != "a"){
    a=Serial.read();
  }
}
 
void loop() { 
  // read the pot values:
  Pot1_row_value = analogRead(Pot1);
  Pot2_row_value = analogRead(Pot2);
  
  // Convert the row values (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage_Pot1 = Pot1_row_value*(5.0 / 1023.0);
  float voltage_Pot2 = Pot2_row_value*(5.0 / 1023.0);
  float voltage[]= {voltage_Pot1, voltage_Pot2}; 
  
 
  // print the results to the serial monitor: 
  Serial.print(voltage[0]);
  Serial.print("\t");
  Serial.println(voltage[1]);
  
  // wait 20 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(20);
 
  // read serial data from remote device
  char data = Serial.read();
  //wait available data
  while(Serial.read()&&Serial.available()); 
  
  // Turn the Leds on
  if (voltage[0]<2.5){
     digitalWrite(Led1, HIGH); //red led
     delay(200);
     digitalWrite(Led1, LOW); //red led
     delay(1500);
    
    }
  if(data == 'b'){
  digitalWrite(Led1, HIGH); //red led
  digitalWrite(Led2, LOW);  //green led
  delay(200);
  digitalWrite(Led1, LOW); //red led
  delay(1500);
  
  }
  else if(data == 'a'){
  digitalWrite(Led2, HIGH);
  digitalWrite(Led1, LOW);
  } 
}
