// Bluetooth Tutorial By Robo India
// Bluetooth module used - HC-06

#include <SoftwareSerial.h>
SoftwareSerial BlueTooth(1, 0); // (TXD, RXD) of HC-06

char BT_input; // to store input character received via BT.

void setup()  
{
  pinMode(9, OUTPUT);     // Arduino Board LED Pin
  BlueTooth.begin(9600);  
}

void loop() 
{
  if (BlueTooth.available())
 
  {
    BT_input=(BlueTooth.read());
    if (BT_input=='a')
    {
      digitalWrite(9, HIGH);
      BlueTooth.println("Now LED is ON");
    }
    else if (BT_input=='b')
    {
      digitalWrite(9, LOW);
      BlueTooth.println("Now LED is OFF");
    }
   else if (BT_input=='?')
    {
      BlueTooth.println("Send 'a' to turn LED ON");
      BlueTooth.println("Send 'b' to turn LED OFF");
    }   
   // You may add other if else condition here. 
  }
}
