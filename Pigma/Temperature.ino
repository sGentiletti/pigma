#include <DHT.h>
#include <DHT_U.h>

#define SENSOR_TEMPERATURE_PIN 7

DHT dht(SENSOR_TEMPERATURE_PIN, DHT22);

void initTemperature() {
  pinMode(SENSOR_TEMPERATURE_PIN, INPUT_PULLUP);
  dht.begin();
}

int getTemperature() {
  return dht.readTemperature();
}
