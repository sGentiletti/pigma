#include <DHT.h>
#include <DHT_U.h>

#define SENSOR_TEMPERATURE_PIN 6

DHT dht(SENSOR_TEMPERATURE_PIN, DHT22);

void initTemperature() {
  digitalWrite(SENSOR_TEMPERATURE_PIN, HIGH);
  dht.begin();
}

int getTemperature() {
  return dht.readTemperature();
}

void resetTemperature() {
  digitalWrite(SENSOR_TEMPERATURE_PIN, LOW);
  delay(500);
  digitalWrite(SENSOR_TEMPERATURE_PIN, HIGH);
}
