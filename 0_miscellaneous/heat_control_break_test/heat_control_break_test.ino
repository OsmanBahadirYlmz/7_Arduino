
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 1000;              //ortalama sıcaklık hesaplama süresi
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const long interval2 = 10000; 
boolean a=false;
boolean iswifisetupok=false;



void setup() {
    Serial.begin(9600);


}

void loop(){

    if (millis()-previousMillis>10000){
      if(iswifisetupok==false) wifisetup();
        senddata();

        previousMillis=millis();
        Serial.print("is wifi");Serial.println(iswifisetupok);


    } 


}

void wifisetup(){
    uint32_t timer_start = millis();
    while(a){
        if (millis() - timer_start>10000UL){
            iswifisetupok=false;
            Serial.println("timeout1");
            break;
        }
        Serial.println("wifi beklenior");
        delay("300");
        iswifisetupok=true;


    }
    Serial.println("Aga Baglandi.");


}

void senddata(){
    Serial.println("datasebd");


}
