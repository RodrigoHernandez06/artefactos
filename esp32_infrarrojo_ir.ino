/*
 * ESP32 + Sensor infrarrojo de obstáculos (FC-51 / módulo IR digital)
 *
 * Conexiones (Sensor -> ESP32)
 *   VCC -> 3.3V (o 5V según el módulo; la salida debe quedar a 3.3V)
 *   GND -> GND
 *   OUT -> GPIO 27
 *
 * El FC-51 normalmente da LOW cuando detecta un obstáculo
 * y HIGH cuando no hay nada. Ajusta el potenciómetro para el alcance
 */

#define IR_PIN  27
#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("Sensor IR listo");
}

void loop() {
  int estado = digitalRead(IR_PIN);

  if (estado == LOW) {            // Obstáculo detectado
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Obstaculo DETECTADO");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Sin obstaculo");
  }

  delay(200);
}
