#include <WiFi.h>

// Prototipo de la función pingAndPrint
void pingAndPrint(const IPAddress& ip);

// Configuración de AP
const char* ap_ssid = "ESP32_AP"; //red wifi
const char* ap_password = "12345678"; //clave de access point

// Configuración de Cliente WiFi
const char* client_ssid = "usuario";  
const char* client_password = "Clave";   

IPAddress ip1(192, 168, 100, 1);
IPAddress ip2(8, 8, 8, 8);
const uint16_t echoPort = 7; 

void setup() {
  Serial.begin(115200);
  
  // Configurar el ESP32 como Cliente WiFi
  WiFi.begin(client_ssid, client_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300); // Reduce el tiempo de espera
  }

  // Configurar el ESP32 como Access Point
  WiFi.softAP(ap_ssid, ap_password);
}

void loop() {
  delay(10000);
  pingAndPrint(ip1);
  pingAndPrint(ip2);
}

// Definición de la función pingAndPrint
void pingAndPrint(const IPAddress& ip) {
  WiFiClient client;

  if (client.connect(ip, echoPort)) {
    Serial.printf("Conexión a %s exitosa\n", ip.toString().c_str());
    client.stop();
  } else {
    Serial.printf("Conexión a %s fallida\n", ip.toString().c_str());
  }
}
