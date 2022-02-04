#define fc33 2

int motor1pin1 = 5;
int motor1pin2 = 6;
int motor1pin3= 7;

int motor2pin1 = 13;
int motor2pin2 = 12;
int counter=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor1pin3, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
  pinMode(fc33,INPUT);
  Serial.begin(9600);
 
}

void loop() {
  // put your main code here, to run repeatedly:   
 // digitalWrite(motor1pin1, HIGH);
 //digitalWrite(motor1pin2, LOW);
digitalWrite(motor1pin3,HIGH);
digitalWrite(motor1pin2,LOW);
analogWrite(motor1pin1,45);
delay(300);
analogWrite(motor1pin1,65);
delay(300);
analogWrite(motor1pin1,85);
delay(300);
analogWrite(motor1pin1,105);
delay(300);

int val=digitalRead(fc33);
if (!val) counter=counter+1;


Serial.print("counter");Serial.println(counter);



}
