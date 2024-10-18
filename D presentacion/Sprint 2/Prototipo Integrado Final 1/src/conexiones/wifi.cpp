#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Preferences.h>  // Biblioteca para manejar NVS (memoria no volátil)

// Definimos los nombres de las credenciales en NVS
Preferences preferences;
const char* PREF_WIFI_SSID = "wifi_ssid";
const char* PREF_WIFI_PASS = "wifi_pass";

// Variables globales para WiFi
String ssid, password;
bool datosGuardados = false;

// Función para leer los datos de WiFi desde el usuario
void pedirDatosWiFi() {
  Serial.println("Introduzca el nombre de la red WiFi:");
  while (Serial.available() == 0);  // Espera por la entrada del usuario
  ssid = Serial.readStringUntil('\n');  // Lee la entrada del nombre de la red
  
  Serial.println("Introduzca la contraseña:");
  while (Serial.available() == 0);  // Espera por la entrada del usuario
  password = Serial.readStringUntil('\n');  // Lee la entrada de la contraseña
}

// Función para guardar los datos WiFi en NVS
void guardarDatosWiFi() {
  preferences.begin("wifi", false);
  preferences.putString(PREF_WIFI_SSID, ssid);
  preferences.putString(PREF_WIFI_PASS, password);
  preferences.end();
  Serial.println("Datos de WiFi guardados en memoria.");
}

// Función para conectarse a la red WiFi
void conectarWiFi() {
  if (datosGuardados) {
    ssid = preferences.getString(PREF_WIFI_SSID, "");
    password = preferences.getString(PREF_WIFI_PASS, "");
  } else {
    pedirDatosWiFi();  // Pide los datos si no están guardados
  }
  
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Conectando a Wi-Fi...");
  
  int intentos = 0;
  while (WiFi.status() != WL_CONNECTED && intentos < 20) {
    delay(500);
    Serial.print(".");
    intentos++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado a Wi-Fi, IP: " + WiFi.localIP().toString());
    
    // Pregunta si quiere guardar los datos
    if (!datosGuardados) {
      Serial.println("¿Desea guardar esta red como predeterminada? (S/n)");
      while (Serial.available() == 0);  // Espera por la entrada
      char respuesta = Serial.read();
      if (respuesta == 'S' || respuesta == 's') {
        guardarDatosWiFi();
        datosGuardados = true;
      }
    }
  } else {
    Serial.println("\nNo se pudo conectar a la red WiFi.");
  }
}

// Función para mostrar el estado de la conexión WiFi
void estadoWiFi() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Estado de la conexión WiFi:");
    Serial.println("SSID: " + WiFi.SSID());
    Serial.println("IP: " + WiFi.localIP().toString());
    Serial.println("RSSI: " + String(WiFi.RSSI()) + " dBm");
    Serial.println("Velocidad: " + String(WiFi.channel()));
  } else {
    Serial.println("No conectado a Wi-Fi.");
  }
}

// Función para crear un punto de acceso (AP) mientras está conectado a WiFi
void iniciarAP() {
  WiFi.softAP("ESP32_AP", "12345678");  // Nombre del AP y contraseña
  Serial.println("Punto de acceso iniciado, IP: " + WiFi.softAPIP().toString());
}

void setup() {
  Serial.begin(115200);
  
  // Inicializa la memoria no volátil (NVS)
  preferences.begin("wifi", true);  // Modo solo lectura para verificar si hay datos guardados
  if (preferences.getString(PREF_WIFI_SSID, "") != "") {
    datosGuardados = true;
  }
  preferences.end();
  
  conectarWiFi();  // Intenta conectarse
  
  // Iniciar el punto de acceso
  iniciarAP();
  
  // Mostrar el estado de WiFi
  estadoWiFi();
}

void loop() {
  // Manejo de la conexión WiFi y sus tareas relacionadas
  delay(10000);  // Tiempo de espera antes de mostrar el estado nuevamente
  estadoWiFi();  // Muestra estado de la conexión cada 10 segundos
}
