/*
 * ESP32 + RFID RC522
 * Librería: "MFRC522" (Instalar desde el Gestor de bibliotecas)
 *
 * Conexiones (RC522 -> ESP32) ¡Alimentar con 3.3V, NO 5V!
 *   SDA (SS)  -> GPIO 5
 *   SCK       -> GPIO 18
 *   MOSI      -> GPIO 23
 *   MISO      -> GPIO 19
 *   RST       -> GPIO 22
 *   3.3V      -> 3V3
 *   GND       -> GND
 *   (IRQ no se conecta)
 */

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN  5
#define RST_PIN 22
#define LED_PIN 2   // LED integrado

MFRC522 rfid(SS_PIN, RST_PIN);

// UID autorizado (cámbialo por el de tu tarjeta; léelo primero por el monitor serie)
byte uidAutorizado[] = {0xDE, 0xAD, 0xBE, 0xEF};

bool uidCoincide() {
  if (rfid.uid.size != sizeof(uidAutorizado)) return false;
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] != uidAutorizado[i]) return false;
  }
  return true;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  SPI.begin(18, 19, 23, SS_PIN);  // SCK, MISO, MOSI, SS
  rfid.PCD_Init();
  Serial.println("Acerca una tarjeta o llavero al lector...");
}

void loop() {
  // Esperar una tarjeta nueva
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  // Mostrar UID
  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Verificar acceso
  if (uidCoincide()) {
    Serial.println("Acceso PERMITIDO");
    digitalWrite(LED_PIN, HIGH);
    delay(1500);
    digitalWrite(LED_PIN, LOW);
  } else {
    Serial.println("Acceso DENEGADO");
  }

  rfid.PICC_HaltA();        // Detener lectura de la tarjeta
  rfid.PCD_StopCrypto1();
}
