#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11 //DHT 11
//#define DEBUG
DHT dht(DHTPIN, DHTTYPE);
const int Buffer_size=255;
char Buffer[Buffer_size]; 
float Humidity=0.0,Temperature=0.0;
void setup() {
  Serial.begin(9600);
  #ifdef DEBUG
    Serial.println("DHTxx test!");
  #endif
  dht.begin();
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if(h!=Humidity||t!=Temperature){
    Humidity=h;
    Temperature=t;
    #ifdef DEBUG //only when you dont want read on server serial
    Serial.print("New Measurement! Humidity: ");
    Serial.print(Humidity);
    Serial.print("%  Temperature: ");
    Serial.print(Temperature);
    Serial.print("°C ");
    Serial.println("");
    #endif
    sprintf(Buffer,"%d|%d|%d;",1,int(Temperature),int(Humidity));
    if(Serial.availableForWrite()>strlen(Buffer)){
      Serial.print(Buffer);
      Serial.flush();
    }
    delay(1000);
  }
}
/////ADITIONAL LIBRARES
//https://github.com/adafruit/DHT-sensor-library
//https://github.com/adafruit/Adafruit_Sensor
