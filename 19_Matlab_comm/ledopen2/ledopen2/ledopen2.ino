

int value;

void setup()
{
Serial.begin(9600);
pinMode(2, OUTPUT);
}

void loop()
{
  if(Serial.available()>0)
  {
    value=Serial.read();

    if  (value == 1)           
    { 
    digitalWrite(2, HIGH);
    }
    else if(value == 0)         
    { 
    digitalWrite(2, LOW);
    }
    else if(value>2 ){
       digitalWrite(2, HIGH);
       delay(value);
       digitalWrite(2, LOW);
       delay(1000);
      }

    
    
    
  }
  delay(1000);
}
