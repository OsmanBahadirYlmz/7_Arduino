//ilgili kütüphanene
#include <FaBoLCD_PCF8574.h>
FaBoLCD_PCF8574 lcd;





int Incoming_value = 0;                //Variable for storing Incoming_value
void setup() 
{
  Serial.begin(9600);         //Sets the data rate in bits per second (baud) for serial data transmission
  pinMode(2, OUTPUT);        //Sets digital pin 13 as output pin
  lcd.begin(16, 2);  


}
void loop()
{
  if(Serial.available() > 0)  
  
  {
    Serial.print("serial avaible");
    Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value
    Serial.print(Incoming_value);        //Print Value of Incoming_value in Serial monitor
    Serial.print("\n");        //New line 
    if(Incoming_value == 'W')  {          //Checks whether value of Incoming_value is equal to 1 
      digitalWrite(2, HIGH);  //If value is 1 then LED turns ON
      Serial.print("LEDon");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("On Isik Acma");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");
      }
    else if(Incoming_value == 'w'){    //Checks whether value of Incoming_value is equal to 0
      digitalWrite(2, LOW);   //If value is 0 then LED turns OFF
      Serial.print("LEDoff-----");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("On Isik Kapama");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");  
    
    } 

    else if(Incoming_value == 'F'){    

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Ileri");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");  
    
    } 
    else if(Incoming_value == 'B'){   

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Geri");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");  
    
    } 
    else if(Incoming_value == 'L'){    

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sol");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");  
    
    } 
    else if(Incoming_value == 'R'){    

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sag");
      lcd.setCursor(0,1);
      lcd.print("Tusuna Basildi");  
    
    } 





      
  }                            
 
}
