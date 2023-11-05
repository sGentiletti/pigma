#include <DHT.h>
#include <DHT_U.h>

#define SENSOR_TEMPERATURE_PIN 7
#define MAX_TEMPERATURE 80
#define MIN_TEMPERATURE 0

DHT dht(SENSOR_TEMPERATURE_PIN, DHT22);

void initTemperature() {
  noInterrupts();
  TCCR1A = 0;              // Configuración inicial del Timer 1
  TCCR1B = 0;              // Detener el Timer 1
  TCCR1B |= (1 << CS11);   // Configura preescala a 256 para el Timer 1 (7812.5Hz)
  TIMSK1 |= (1 << TOIE1);  // Habilita la interrupción por desbordamiento del Timer 1
  interrupts();
  dht.begin();
}

int getTemperature() {
  return dht.readTemperature();
}

ISR(TIMER1_OVF_vect) {                        // Esto se ejecuta cada 32.64mS. (Es una interrupcion por desbordamiento de clock)
  static unsigned long lastInterruption = 0;  // Esta variable se instancia una unica vez

  if (!isHeatingOn) {  // Resistencia apagada entonces salir sin hacer nada
    return;
  }

  // --- Resistencia Prendia ---

  if (getButtonStatus()) {  // Cancelar proceso al tocar el pulsador
    abortSequence();
    resetSoftware();
  }

  unsigned long interruptionTime = millis();

  if (interruptionTime - lastInterruption > 1000) {  // Esto se ejecuta cada 1s
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