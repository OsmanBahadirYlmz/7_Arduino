// set PushButton pin number
const int buttonPin = 2;

// set LED pin numbers
const int LED1 = 8;
const int LED2 = 9;

// set LED pin 13
const int LEDP13 = 13;

//initialising led
int LED1Status = LOW;
int LED2Status = LOW;

int buttonState;

unsigned long timePress = 0;
unsigned long timePressLimit = 0;
int clicks = 0;

void setup() {
  // put your setup code here, to run once:
  
  // initialize the LED pin as an output:
  pinMode(buttonPin ,INPUT);
 
  // initialize the pushbutton pin as an input:
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  
  buttonState = digitalRead(buttonPin);
  
  if (buttonState == HIGH){
    delay(200);
    Serial.println("Button Pressed");
    
    if (clicks == 0) {
    timePress = millis();
    timePressLimit = timePress + 1000;    
    clicks = 1;
    }

    else if (clicks == 1 && millis() < timePressLimit){
      Serial.println("Button Pressed twice");
     
     //Double Press Action
       Serial.println("action 1");
     if (LED2Status == LOW){
      digitalWrite(LED2, HIGH);
      LED2Status = HIGH;
     }

     else if (LED2Status == HIGH){
      digitalWrite(LED2, LOW);
      LED2Status = LOW;
     }    

     //set variables back to 0
      timePress = 0;
      timePressLimit = 0;
      clicks = 0;      
    }    
  }

  if (clicks == 1 && timePressLimit != 0 && millis() > timePressLimit){
     Serial.println("Button Pressed Once");
     timePress = 0;
     timePressLimit = 0;
     clicks = 0;

     //one click Press Action
     Serial.println("action 2");
     if (LED1Status == LOW){
      digitalWrite(LED1, HIGH);
      LED1Status = HIGH;
     }

     else if (LED1Status == HIGH){
      digitalWrite(LED1, LOW);
      LED1Status = LOW;
     }
  }
}
