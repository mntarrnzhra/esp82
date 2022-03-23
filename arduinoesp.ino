#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "4k";
const char* password = "qwertyuio";
const char* serverName = "http://192.168.43.187/servo/all_data.php";

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

void setup() {
  pinMode(11, OUTPUT);  
  pinMode(12, INPUT);    
  Serial.begin(9600);  
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED){
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("Terhubung ke Jaringan WiFi dengan IP Adderss: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if((millis() - lastTime) > timerDelay){
    //testing data random
    float tegangan = random(0,100);
    float suhu = random(0,50);
    float ultrasonik= random(0,50);
// float ultrasonik= jarak();
//   digitalWrite(11, LOW);
//  delayMicroseconds(8);
//  digitalWrite(11, HIGH);
//  delayMicroseconds(8);
//  digitalWrite(11, LOW);
//  delayMicroseconds(8);
//  durasi = pulseIn(12, HIGH); //
//  jarak = (durasi / 2) / 29.1;  //
//  Serial.println(jarak); 

    if(WiFi.status() == WL_CONNECTED){
      HTTPClient http;

      String url = serverName;
      url += "?tegangan=";
      url += tegangan;
      url += "&suhu=";
      url += suhu;
      url += "&ultrasonik=";
      url += ultrasonik;     
      http.begin(url.c_str());

     request
      int httpResponseCode = http.GET();

      if(httpResponseCode > 0){
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else{
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }

      http.end();
    }
    else{
      Serial.println("WiFi disconnected");
    }
    lastTime = millis();
  }
}
