#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "nodemcu2-3ec0e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AmNXI0pdfVrguNBDuy6sp05DQA1XkdDWoy3Jr0zN"
#define WIFI_SSID "Xiaomi"
#define WIFI_PASSWORD "33355555"

String yer1="boş";
String yer2="boş";
String yer3="boş";
String yer4="boş";
String yer5="boş";
String yer6="boş";

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  pinMode(D2,OUTPUT);
}

void firebaseupt(){
  Firebase.setString("yer1",yer1);
  Firebase.setString("yer2",yer2);
  Firebase.setString("yer3",yer3);
  Firebase.setString("yer4",yer4);
  Firebase.setString("yer5",yer5);
  Firebase.setString("yer6",yer6);
    

  
}
void loop() {

  Serial.println("123-1");
  yer1="dolu";
  yer2="dolu";
  yer3="dolu";
  yer6="boş";
  
  
  
  firebaseupt();
  delay(3000);
  Serial.println("456-1");
  yer4="dolu";
  yer5="dolu";
  yer5="dolu";
  firebaseupt();
  delay(3000);
  
  Serial.println("hepsi-0");
  yer1="boş";
  yer2="boş";
  yer3="boş";
  yer4="boş";
  yer5="boş";
  yer6="boş";
  firebaseupt();
  delay(3000);
  
 if (Firebase.failed()) {
      Serial.print("yer:");
      Serial.println(Firebase.error());  
      return;
  }

  String lampstatus=Firebase.getString("lamp");
  Serial.print("lamp: ");Serial.println(lampstatus);

  if(lampstatus=="1"){
    digitalWrite(D2,HIGH);    
  }
  else if(lampstatus=="0"){
    digitalWrite(D2,LOW);
    
  }












  
}
