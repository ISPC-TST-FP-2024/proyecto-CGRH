#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Preferences.h>  // Para guardar credenciales en la memoria no volátil (NVS)
#include "wifi.h"

Preferences preferences; // Objeto para manejar la memoria no volátil

String ssid;
String password;

String user = "xxxx";  // Datos del usuario
String pass = "xxxx";  // Datos del usuario

void iniciarWiFi() {
  // Ver si hay credenciales guardadas en la memoria
  preferences.begin("wifiCreds", true);  // true es modo de solo lectura
  ssid = preferences.getString("ssid", "");
  password = preferences.getString("password", "");
  preferences.end();

  if (ssid == "" || password == "") {
    Serial.println("No se encontraron credenciales guardadas.");
    return;
  }

  // Intentar conectar con credenciales guardadas
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Conectando a Wi-Fi: ");
  Serial.println(ssid);

  int max_attempts = 20;  // Máximo de intentos antes de fallo
  while (WiFi.status() != WL_CONNECTED && max_attempts-- > 0) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado a Wi-Fi, IP: " + WiFi.localIP().toString());
  } else {
    Serial.println("\nNo se pudo conectar a Wi-Fi.");
  }
}

void conectarWiFiManual(const char* new_ssid, const char* new_password) {
  WiFi.begin(new_ssid, new_password);
  Serial.print("Intentando conectar a la red Wi-Fi: ");
  Serial.println(new_ssid);

  int max_attempts = 20;  // Máximo de intentos
  while (WiFi.status() != WL_CONNECTED && max_attempts-- > 0) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado a Wi-Fi, IP: " + WiFi.localIP().toString());
    
    // Preguntar si se debe guardar esta red como predeterminada
    Serial.println("¿Quieres guardar esta red como predeterminada? (y/n)");
    while (!Serial.available());  // Esperar por la respuesta del usuario
    char response = Serial.read();
    
    if (response == 'y' || response == 'Y') {
      guardarCredenciales(new_ssid, new_password);
      Serial.println("Red guardada como predeterminada.");
    } else {
      Serial.println("Red no guardada.");
    }
  } else {
    Serial.println("\nNo se pudo conectar a la red Wi-Fi.");
  }
}

void guardarCredenciales(const char* ssid, const char* password) {
  // Guardar credenciales en la memoria no volátil
  preferences.begin("wifiCreds", false);  // false es modo de escritura
  preferences.putString("ssid", ssid);
  preferences.putString("password", password);
  preferences.end();
}

void borrarCredenciales() {
  // Borrar las credenciales de la memoria
  preferences.begin("wifiCreds", false);  // false es modo de escritura
  preferences.clear();  // Eliminar todas las entradas en el espacio "wifiCreds"
  preferences.end();
  Serial.println("Credenciales Wi-Fi eliminadas.");
}

void manejarWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String datos_a_enviar = "?user=" + user + "&pass=" + pass;
    
    http.begin("http://www.tuservidor.com/php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    int codigo_respuesta = http.POST(datos_a_enviar);

    if (codigo_respuesta > 0) {
      Serial.println("Código HTTP: " + String(codigo_respuesta));
      if (codigo_respuesta == HTTP_CODE_OK) {
        String respuesta = http.getString();
        Serial.println("Respuesta del servidor: " + respuesta);
      }
    } else {
      Serial.println("Error en la conexión HTTP.");
    }
    http.end();
  } else {
    Serial.println("No conectado a Wi-Fi.");
  }

  delay(2000);  // Evitar spam excesivo de peticiones
}

void desconectarWiFi() {
  WiFi.disconnect();
  Serial.println("Wi-Fi desconectado.");
}

void verEstadoWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Estado de Wi-Fi: Conectado");
    Serial.println("SSID: " + WiFi.SSID());
    Serial.println("IP: " + WiFi.localIP().toString());
    Serial.println("RSSI: " + String(WiFi.RSSI()));  // Intensidad de la señal
  } else {
    Serial.println("Estado de Wi-Fi: No conectado");
  }
}
