int Incoming_value = 0;                //Variable for storing Incoming_value
void setup() 
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(9, OUTPUT);        //Sets digital pin 13 as output pin
}
void loop()
{
  if(Serial.available() > 0)  
  
  {
    Serial.print("serial avaible");
    Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");        //New line 
    if(Incoming_value == '1')  {          //Checks whether value of Incoming_value is equal to 1 
      digitalWrite(9, HIGH);  //If value is 1 then LED turns ON
      Serial.print("LEDon++++++");}
    else if(Incoming_value == '0'){    //Checks whether value of Incoming_value is equal to 0
      digitalWrite(9, LOW);   //If value is 0 then LED turns OFF
      Serial.print("LEDoff-----");
  }                            
 
}
}