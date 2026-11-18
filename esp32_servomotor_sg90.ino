/*
 * ESP32 + Servomotor SG90 / MG90S
 * Librería: "ESP32Servo" (Instalar desde el Gestor de bibliotecas)
 *
 * Conexiones (Servo -> ESP32)
 *   Señal (naranja/amarillo) -> GPIO 18
 *   VCC (rojo)               -> 5V (idealmente fuente externa de 5V)
 *   GND (marrón/negro)       -> GND (común con el ESP32)
 *
 * IMPORTANTE: si el servo hace temblar o reiniciar el ESP32,
 * aliméntalo con una fuente externa de 5V y une las tierras (GND).
 */

#include <ESP32Servo.h>

#define SERVO_PIN 18

Servo miServo;

void setup() {
  Serial.begin(115200);
  miServo.setPeriodHertz(50);               // 50 Hz estándar para servos
  miServo.attach(SERVO_PIN, 500, 2400);     // pin, pulso mín (µs), pulso máx (µs)
  Serial.println("Servo listo");
}

void loop() {
  // Barrido de 0° a 180°
  for (int angulo = 0; angulo <= 180; angulo += 2) {
    miServo.write(angulo);
    delay(15);
  }
  Serial.println("180 grados");
  delay(500);

  // Barrido de 180° a 0°
  for (int angulo = 180; angulo >= 0; angulo -= 2) {
    miServo.write(angulo);
    delay(15);
  }
  Serial.println("0 grados");
  delay(500);
}
