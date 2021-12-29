int motor1pin1 = 8;
int motor1pin2 = 9;

int motor2pin1 = 13;
int motor2pin2 = 12;
#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(1, 0); // (TXD, RXD) of HC-06

char BT_input; // to store input character received via BT.

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  
  BlueTooth.begin(9600);  
}

void loop() {

if (BlueTooth.available())
 
  {
    BT_input=(BlueTooth.read());
    if (BT_input=='a')
    {

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
   
    
    BlueTooth.println("Now LED is ON a");
    delay(500);

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);



     
     
     }
    else if (BT_input=='b')
    {  
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
 
    
    BlueTooth.println("Now LED is OFF b");
    delay(500);

    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, LOW);

    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, LOW);


    }
   else if (BT_input=='?')
    {
      BlueTooth.println("Send 'a' to turn LED ON");
      BlueTooth.println("Send 'b' to turn LED OFF");
    }   








  // put your main code here, to run repeatedly:   
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  Serial.print("pos");Serial.println("");
  delay(5000);


  }}
