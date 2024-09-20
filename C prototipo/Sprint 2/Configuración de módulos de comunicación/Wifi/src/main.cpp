#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "wifi";           // Nombre de la red Wi-Fi
const char* password = "Contra";     // Contraseña de la red Wi-Fi

String user = "xxxx";             // Datos de usuario a enviar
String pass = "xxxx";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Conectar a Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a Wi-Fi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Conectado con éxito, IP asignada: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {  // Verificar si está conectado a Wi-Fi
    HTTPClient http;                    // Crear un objeto HTTPClient
    String datos_a_enviar = "?user=" + user + "&pass=" + pass; // Datos a enviar
    
    http.begin("http://www.tuservidor.com/php");  // URL del servidor
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  // Añadir cabecera de contenido
    int codigo_respuesta = http.POST(datos_a_enviar);  // Enviar datos vía POST

    if (codigo_respuesta > 0) {
      Serial.println("Código HTTP: " + String(codigo_respuesta));
      
      if (codigo_respuesta == HTTP_CODE_OK) {  // Si el servidor respondió correctamente
        String respuesta = http.getString();   // Leer respuesta del servidor
        Serial.println("Respuesta del servidor:");
        Serial.println(respuesta);
      }
    } else {
      Serial.println("Error en la conexión HTTP.");
    }

    http.end();  // Cerrar la conexión
  } else {
    Serial.println("No conectado a Wi-Fi.");
  }

  delay(2000);  // Esperar 2 segundos para la siguiente solicitud
}
