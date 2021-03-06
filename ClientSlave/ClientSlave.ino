#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#define DEBUG
WiFiUDP Udp;
const char Ssid[] = "SSID";
const char Password[] = "PASS";
const char Ip[] = "server.local.ip.adress";
//1 for master, 2 .... for slave
const int DeviceID = 3;
const unsigned int Port = 7654;
const int Buffer_size=255;
char Buffer[Buffer_size]; 
const int Delay=4000;
void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(Ssid, Password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println("Connected!");
  Udp.begin(Port);
  pinMode(A0,INPUT);
  //waiting for the sensor to be ready to send valid data
  for(int i=0;i<10;i++){
    int temp=analogRead(A0);
    #ifdef DEBUG
    Serial.print("Waiting for valid data: ");
    Serial.print(temp);
    Serial.println("");
    #endif
    delay(1000);
  }
}
void loop() {
  sprintf(Buffer,"%d|%d;",DeviceID,analogRead(A0));
  #ifdef DEBUG
  Serial.println(Buffer);
  #endif
  if(Udp.beginPacket(Ip, Port)){
    Udp.write(Buffer);
    Udp.endPacket();
  }
  delay(Delay);
}
