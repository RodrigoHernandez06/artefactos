/*
 * ESP32 + Sensor de temperatura LM35
 *
 * Conexiones (LM35 -> ESP32)
 *   Pin 1 (+Vs)  -> 5V (pin VIN)
 *   Pin 2 (Vout) -> GPIO 34 (entrada ADC1, solo lectura)
 *   Pin 3 (GND)  -> GND
 *
 * El LM35 entrega 10 mV por cada °C (a 25 °C = 250 mV).
 * Se usa ADC1 (GPIO 32-39) porque ADC2 falla si se usa WiFi.
 * Recomendado: condensador de 100 nF entre Vout y GND para reducir ruido.
 */

#define LM35_PIN  34
#define MUESTRAS  20

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);                         // 0 - 4095
  analogSetPinAttenuation(LM35_PIN, ADC_11db);      // Rango ~0 - 3.1 V
  Serial.println("LM35 listo");
}

float leerTemperaturaC() {
  uint32_t suma_mV = 0;
  for (int i = 0; i < MUESTRAS; i++) {
    suma_mV += analogReadMilliVolts(LM35_PIN);      // Lectura ya calibrada en mV
    delay(5);
  }
  float mV = suma_mV / (float)MUESTRAS;
  return mV / 10.0;                                 // 10 mV = 1 °C
}

void loop() {
  float tempC = leerTemperaturaC();
  float tempF = tempC * 9.0 / 5.0 + 32.0;

  Serial.print("Temperatura: ");
  Serial.print(tempC, 1);
  Serial.print(" °C  |  ");
  Serial.print(tempF, 1);
  Serial.println(" °F");

  delay(1000);
}
