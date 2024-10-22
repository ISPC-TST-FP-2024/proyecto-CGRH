// Probar la conexión a una red WiFi local y verificar la obtención de una dirección IP.
#include <WiFi.h>

const char* ssid = "Prueba";      // Reemplaza con tu SSID
const char* password = "nicolasb";  // Reemplaza con tu contraseña

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando a ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConectado a la red WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Mantener la conexión establecida
}
