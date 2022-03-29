/*
wifi modul-2 turuncu 3,5v,sarı pin10,beyaz pin11,gri ground  

*/




#include <DHT.h>
#define DHTPIN 2 
#define DHTTYPE    DHT22 
DHT dht(DHTPIN, DHTTYPE);


//wifi eklentileri
#include <SoftwareSerial.h>
String agAdi="obymi";
String agSifresi="1234567883";
int rxPin=10;
int txPin=11;
String ip= "184.106.153.149";
boolean iswifisetupok=false;



SoftwareSerial esp(rxPin,txPin);
unsigned long currentMillis=0;
unsigned long previousMillis3 = 0;
const long interval3 = 60000; 


double T=20; //sensörden ölçülen anlık sıcaklık null olabilir
double T0=20;//anlık sıcaklık null değil
double H;

void setup() {
Serial.begin(9600);
dht.begin();
delay(2000);


Serial.println("Started");
  esp.begin(115200);                                          //ESP8266 ile seri haberleşmeyi başlatıyoruz.
  esp.println("AT");                                          //AT komutu ile modül kontrolünü yapıyoruz.
  Serial.println("AT Yollandı");
  while(!esp.find("OK")){                                     //Modül hazır olana kadar bekliyoruz.
   
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadı.");
    iswifisetupok=true;
  }
  Serial.println("OK Komutu Alındı");
  esp.println("AT+CWMODE=1");                                 //ESP8266 modülünü client olarak ayarlıyoruz.
  while(!esp.find("OK")){                                     //Ayar yapılana kadar bekliyoruz.
   
    iswifisetupok=true;
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapılıyor....");
  }
  Serial.println("Client olarak ayarlandı");
  Serial.println("Aga Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    //Ağımıza bağlanıyoruz.
  while(!esp.find("OK")){                                       //Ağa bağlanana kadar bekliyoruz.
    
    Serial.println("Aga sorunu, while");
  }
  if (iswifisetupok){
    Serial.println("Aga Baglandi.");
    
  }
else {
    Serial.println("Ag sorunu var.");
   

}

}


void loop() {
currentMillis = millis();



//read temparature and chack is null
T=dht.readTemperature();
H=dht.readHumidity();
if(T<70 && T>-30) T0=T;
Serial.print("T: ");Serial.println(T);
Serial.print("T0: ");Serial.println(T0);
Serial.print("H: ");Serial.println(H);

//wifi setup veri gönderme
if (currentMillis - previousMillis3 >= interval3)
{
  
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           //Thingspeak'e bağlanıyoruz.
  if(esp.find("Error")){                                      //Bağlantı hatası kontrolü yapıyoruz.
    Serial.println("AT+CIPSTART Error");
  }
  //DHT11.read(dht11Pin);

  //orjinal kod bu ama T0 ile değiştirildi
  //sicaklik = (float)dht.readTemperature();; 
  //nem = (float)DHT11.humidity;
  String veri = "GET https://api.thingspeak.com/update?api_key=WMULLJWPU82ZRD5Y";   //Thingspeak komutu. Key kısmına kendi api keyimizi yazıyoruz.                                   //Göndereceğimiz sıcaklık değişkeni
  veri += "&field1=";
  veri += String(T0);
  veri += "&field2=";
  veri += String(H);                                        //Göndereceğimiz nem değişkeni
  veri += "\r\n\r\n"; 
  esp.print("AT+CIPSEND=");                                   //ESP'ye göndereceğimiz veri uzunluğunu veriyoruz.
  esp.println(veri.length()+2);
  delay(2000);
  if(esp.find(">")){                                          //ESP8266 hazır olduğunda içindeki komutlar çalışıyor.
    esp.print(veri);                                          //Veriyi gönderiyoruz.
    Serial.println(veri);
    Serial.println("Veri gonderildi.");
    delay(1000);
  }
  Serial.println("Baglantı Kapatildi.");
  esp.println("AT+CIPCLOSE");                                //Bağlantıyı kapatıyoruz
  previousMillis3 = currentMillis;


}
//------------------------------------------------





  delay(1000); //Update at every 
  


}



 
