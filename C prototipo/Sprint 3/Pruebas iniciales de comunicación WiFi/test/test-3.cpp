// Validar que las redes WiFi detectadas se muestran correctamente en la consola.

#include <WiFi.h>  // Incluimos la librería para WiFi

void setup() {
  // Inicializamos la comunicación serial para mostrar los resultados
  Serial.begin(115200);
  // Damos un poco de tiempo para iniciar la conexión serial
  delay(1000);

  // Iniciamos el escaneo de redes WiFi
  Serial.println("Iniciando escaneo de redes WiFi...");
  WiFi.mode(WIFI_STA);  // Ponemos el ESP32 en modo estación (cliente WiFi)
  WiFi.disconnect();    // Nos aseguramos de no estar conectado a ninguna red antes del escaneo
  delay(100);

  // Ejecutamos el escaneo de redes WiFi
  int n = WiFi.scanNetworks();
  Serial.println("Escaneo completado.");

  // Mostramos el número de redes detectadas
  if (n == 0) {
    Serial.println("No se encontraron redes WiFi.");
  } else {
    Serial.print(n);
    Serial.println(" redes WiFi encontradas:");
    // Recorremos las redes encontradas
    for (int i = 0; i < n; i++) {
      // Mostramos el SSID (nombre de la red), la potencia de la señal (RSSI) y si la red es protegida o no
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));           // Nombre de la red (SSID)
      Serial.print(" (Señal: ");
      Serial.print(WiFi.RSSI(i));           // Potencia de la señal
      Serial.print(" dBm) Canal: ");
      Serial.print(WiFi.channel(i));        // Canal de la red
      Serial.print(" Encriptado: ");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? "No" : "Sí");
      delay(10);
    }
  }
}

void loop() {
  // El loop está vacío porque el escaneo solo lo hacemos una vez al inicio
}

