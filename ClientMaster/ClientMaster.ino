#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11 //DHT 11
//#define DEBUG //only when you dont want read on server serial
//#define DEBUG2 //only when you dont want read on server serial
DHT dht(DHTPIN, DHTTYPE);
const int Buffer_size=255;
char Buffer[Buffer_size]; 
int Humidity=0,Temperature=0;
const int Skip_delay=8000;
const int Delay=2000;
int Cycle=0;
void setup() {
  Serial.begin(9600);
  #ifdef DEBUG
    Serial.println("DHTxx test!");
  #endif
  dht.begin();
}
void loop() {
  int h = int(dht.readHumidity());
  int t = int(dht.readTemperature());
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if(h!=Humidity||t!=Temperature){
    Humidity=h;
    Temperature=t;
    #ifdef DEBUG 
    Serial.println("");
    Serial.print("New Measurement! Humidity: ");
    Serial.print(Humidity);
    Serial.print("%  Temperature: ");
    Serial.print(Temperature);
    Serial.print("°C ");
    Serial.println("");
    Serial.flush();
    #endif
    //1 is device id - 1 means master
    sprintf(Buffer,"%d|%d|%d;",1,Temperature,Humidity);
    int len=strlen(Buffer);
    #ifdef DEBUG2
    Serial.println("");
    Serial.print("Serial buffer ");
    Serial.print(Serial.availableForWrite());
    Serial.print(" Len ");
    Serial.print(len);
    Serial.println("");
    Serial.flush();
    #endif
    if(Serial.availableForWrite()>len){
      Serial.print(Buffer);
      Serial.flush();
      Cycle=0;
    }
  }
  else{
    Cycle++;
    if(Cycle*Delay>=Skip_delay){
      sprintf(Buffer,"%d|%d|%d;",1,Temperature,Humidity);
      int len=strlen(Buffer);
      if(Serial.availableForWrite()>len){
        Serial.print(Buffer);
        Serial.flush();
        Cycle=0;
      }
    }
  }
  delay(Delay);
}
/////ADITIONAL LIBRARES
//https://github.com/adafruit/DHT-sensor-library
//https://github.com/adafruit/Adafruit_Sensor
