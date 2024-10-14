// Desconectar manualmente el WiFi y reconectar utilizando la funcionalidad del menú.
#include <WiFi.h>

const char* ssid = "Prueba";      // Reemplaza con tu SSID
const char* password = "nicolasb";  // Reemplaza con tu contraseña

void conectarWiFi() {
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

void desconectarWiFi() {
  WiFi.disconnect();
  Serial.println("Desconectado de la red WiFi.");
}

void estadoWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Estado: Conectado");
  } else {
    Serial.println("Estado: Desconectado");
  }
}

void mostrarMenu() {
  Serial.println("\n--- Menú ---");
  Serial.println("1. Conectar a WiFi");
  Serial.println("2. Desconectar WiFi");
  Serial.println("3. Estado de la conexión");
  Serial.println("Elige una opción: ");
}

void setup() {
  Serial.begin(115200);
  mostrarMenu();
}

void loop() {
  if (Serial.available() > 0) {
    int opcion = Serial.parseInt();

    switch (opcion) {
      case 1:
        conectarWiFi();
        break;
      case 2:
        desconectarWiFi();
        break;
      case 3:
        estadoWiFi();
        break;
      default:
        Serial.println("Opción no válida");
        break;
    }

    // Mostrar el menú nuevamente después de realizar una acción
    mostrarMenu();
  }
}
