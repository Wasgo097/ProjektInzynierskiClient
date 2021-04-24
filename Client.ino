#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#define slave
//#define master
WiFiUDP Udp;
const char Ssid[] = "SSID";
const char Password[] = "Pass";
const char Ip[] = "Server.local.ip.address";
const int DeviceID = 1;
const unsigned int Port = 7654;
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
  #ifdef slave
  sprintf(Buffer,"%d|%d",DeviceID,analogRead(A0));
  #elif  master
  sprintf(Buffer,"%d|%d|%d",DeviceID,Temperature,Humidity);
  #else
  sprintf(Buffer,"Error");
  #endif
  //Serial.println(Buffer);
  if(Udp.beginPacket(Ip, Port)){
    Udp.write(Buffer);
    Udp.endPacket();
  }
  delay(1000);
}
