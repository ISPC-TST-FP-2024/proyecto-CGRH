// Realizar pruebas de estabilidad de la conexión (verificar caídas de red y reconexión).
#include <WiFi.h>

// Reemplaza con el SSID y la contraseña de tu red WiFi
const char* ssid = "nombreWifi";
const char* password = "CONTRASEÑA";

unsigned long previousMillis = 0;   // Variable para almacenar el último tiempo de verificación
const long interval = 10000;        // Intervalo de verificación (cada 10 segundos)

void setup() {
  Serial.begin(115200);
  
  // Intentar conectarse a la red WiFi
  WiFi.begin(ssid, password);
  Serial.println("Conectando a WiFi...");
  
  // Esperar hasta que se conecte
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  // Cuando se conecte, mostrar la dirección IP
  Serial.println("");
  Serial.println("Conectado a la red WiFi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Comprobar el estado de la conexión periódicamente
  unsigned long currentMillis = millis();
  
  // Verificar la conexión cada 10 segundos
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Conexión WiFi perdida. Intentando reconectar...");

      // Intentar reconectarse
      WiFi.disconnect();
      WiFi.begin(ssid, password);

      // Esperar hasta reconectar o fallar
      int retryCount = 0;
      while (WiFi.status() != WL_CONNECTED && retryCount < 5) {
        delay(1000);
        Serial.print(".");
        retryCount++;
      }

      // Verificar si la reconexión fue exitosa
      if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nReconexión exitosa.");
        Serial.print("Dirección IP: ");
        Serial.println(WiFi.localIP());
      } else {
        Serial.println("\nNo se pudo reconectar.");
      }
    } else {
      Serial.println("Conexión WiFi estable.");
    }
  }
}
