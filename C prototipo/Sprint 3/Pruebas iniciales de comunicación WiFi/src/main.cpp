#include <WiFi.h>

// Reemplaza con el SSID y la contraseña de tu red WiFi
const char* ssid = "Prueba";
const char* password = "nicolasb";

void setup() {
  // Iniciar la comunicación serial
  Serial.begin(115200);

  // Iniciar WiFi con las credenciales guardadas en NVS (si existen)
  WiFi.begin(ssid, password);

  // Esperar hasta que se conecte al WiFi
  Serial.println("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  // Mostrar la dirección IP asignada
  Serial.println("");
  Serial.println("Conectado a la red WiFi.");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Mantener el programa en funcionamiento
  delay(10000);
}