#include <DHT.h>
#include <DHT_U.h>

int SENSOR_TEMPERATURE_PIN = 7;
int MAX_TEMPERATURE = 80;
int MIN_TEMPERATURE = 10;

DHT dht(SENSOR_TEMPERATURE_PIN, DHT22);

void initTemperature() {
  SREG = (SREG & 0b01111111);               // Desabilitar interrupciones
  TIMSK2 = TIMSK2 | 0b00000001;             // Habilita la interrupcion por desbordamiento
  TCCR2B = 0b00000111;                      // Configura preescala para que FT2 sea de 7812.5Hz
  SREG = (SREG & 0b01111111) | 0b10000000;  // Habilitar interrupciones
  dht.begin();
}

int getTemperature() {
  return dht.readTemperature();
}

ISR(TIMER2_OVF_vect) {                        // Esto se ejecuta cada 32.64mS. (Es una interrupcion por clock)
  static unsigned long lastInterruption = 0;  // Esta variable se instancia una unica vez

  if (!isHeatingOn) {  // Resistencia apagada entonces salir sin hacer nada
    return;
  }

  // --- Resistencia Prendia ---

  unsigned long interruptionTime = millis();

  if (getButtonStatus()) {  // Cancelar proceso al tocar el pulsador
    delay(500);             // Previene lecturas erroneas
    abortSequence();
    resetSoftware();
  }

  if (interruptionTime - lastInterruption > 5) {  // Esto se ejecuta cada 1s
    int temperature = getTemperature();

    if (temperature >= MAX_TEMPERATURE) {
      abortSequenceDueToOverheating();
    }

    if (temperature < MIN_TEMPERATURE) {
      abortSequenceDueToResistanceIssue();
    }
    lastInterruption = interruptionTime;
  }
}