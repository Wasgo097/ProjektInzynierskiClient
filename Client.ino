#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
WiFiUDP Udp;
const char Ssid[] = "SMIERCIONOSNE 5G 300% MOCY";
const char Password[] = "0987654321";
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
  //Udp.begin(Port);
}
void loop() {
  sprintf(Buffer,"Data: %d",5);
  Serial.println(Buffer);
  if(Udp.beginPacket(Ip, Port)){
    Udp.write(Buffer);
    Udp.endPacket();
  }
  delay(2000);
}
