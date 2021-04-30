#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11// DHT 11
#define DEBUG
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
}
float Humidity=0.0,Temperature=0.0;
void loop() {
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  if(h!=Humidity||t!=Temperature){
    Humidity=h;
    Temperature=t;
    #ifdef DEBUG
    Serial.print("New Measurement! Humidity: ");
    Serial.print(Humidity);
    Serial.print("%  Temperature: ");
    Serial.print(Temperature);
    Serial.print("°C ");
    Serial.println("");
    #endif
  }
}
/////ADITIONAL LIBRARES
//https://github.com/adafruit/DHT-sensor-library
//https://github.com/adafruit/Adafruit_Sensor
