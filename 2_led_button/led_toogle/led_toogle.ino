bool flag=0;
bool change=0;
bool ledstate=0;


void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,INPUT);
  Serial.begin(9600);

}

void loop() {

  flag=(digitalRead(3)); // reads botton position
  
  if(flag==1 && change==1){ //if there is a change and button is pressed changes led state
    ledstate=!ledstate;   
    change=0;               //make change 0 in order to not enter same loop again. it causes led blink
  }

  if(flag==0){ //if button relaesed make change 1 so we can go back start position
    change=1;
    
  }



digitalWrite(2,ledstate); 




Serial.print("ledstate: ");Serial.println(ledstate);
Serial.print("change: ");Serial.println(change);
Serial.print("flag: ");Serial.println(flag);
Serial.println("------------------------------------");

delay(10);
}
