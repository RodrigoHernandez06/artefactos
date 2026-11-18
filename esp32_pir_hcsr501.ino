/*
 * ESP32 + Sensor de movimiento PIR (HC-SR501)
 *
 * Conexiones (PIR -> ESP32)
 *   VCC -> 5V (pin VIN del ESP32)
 *   GND -> GND
 *   OUT -> GPIO 27  (la salida es de 3.3V, segura para el ESP32)
 *
 * El PIR necesita ~30-60 s de calentamiento al encender.
 * Potenciómetros del módulo: sensibilidad y tiempo de espera.
 */

#define PIR_PIN 27
#define LED_PIN 2

bool movimientoAnterior = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Calentando sensor PIR (30 s)...");
  delay(30000);
  Serial.println("Sensor listo");
}

void loop() {
  bool movimiento = digitalRead(PIR_PIN) == HIGH;

  // Solo imprimir cuando cambie el estado
  if (movimiento != movimientoAnterior) {
    if (movimiento) {
      Serial.println("¡Movimiento detectado!");
    } else {
      Serial.println("Sin movimiento");
    }
    movimientoAnterior = movimiento;
  }

  digitalWrite(LED_PIN, movimiento ? HIGH : LOW);
  delay(50);
}
