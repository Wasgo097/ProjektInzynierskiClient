#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP Udp;
const char Ssid[] = "****";
const char Password[] = "****";
const char Device[] = "Dev:X_";
const unsigned int Port = 7654;
const char Ip[] = "192.168.99.58";
const int Buffer_size=255;
char Buffer[Buffer_size]; 
void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(Ssid, Password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("Connected!");
  Udp.begin(Port);
  pinMode(A0,INPUT);
}
void loop() {
  sprintf(Buffer,"Data:%d_%s",analogRead(A0),Device);
  //Serial.println(Buffer);
  if(Udp.beginPacket(Ip, Port)){
    Udp.write(Buffer);
    Udp.endPacket();
  }
  delay(1000);
}
