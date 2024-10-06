# Pruebas de conexion wifi para esp32


  1. ESP32 como Access Point (Punto de Acceso): El ESP32 actúa como un punto de acceso y otros dispositivos pueden conectarse a él.
   2. ESP32 como Cliente WiFi (Recibe datos): El ESP32 se conecta a una red WiFi y recibe datos desde un servidor o otro dispositivo.
   3. ESP32 en modo Mixto (Access Point + Cliente): El ESP32 actúa simultáneamente como punto de acceso y cliente, permitiendo la conectividad con una red WiFi y al mismo tiempo ofreciendo un punto de acceso.
---  

1. **ESP32 como Access Point (Punto de Acceso)**

En este modo, el ESP32 crea su propia red WiFi a la que otros dispositivos pueden conectarse.  

```cpp 

#include <WiFi.h>

const char* ssid = "ESP32_AP";
const char* password = "12345678";  // Contraseña de tu red AP

void setup() {
  Serial.begin(115200);

  // Configurar el ESP32 como Access Point
  WiFi.softAP(ssid, password);

  Serial.println("Access Point creado");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());  // Dirección IP del AP
}

void loop() {
  // Aquí puedes manejar las conexiones entrantes si es necesario
}
```  
- Resultado esperado: El ESP32 creará una red llamada "ESP32_AP", a la que puedes conectarte desde otros dispositivos. La dirección IP del punto de acceso será mostrada en la consola.

2. **ESP32 como Cliente WiFi (Recibe Datos de un Servidor)**

Aquí, el ESP32 se conecta a una red WiFi y luego puede enviar y recibir datos de un servidor (por ejemplo, usando un servidor web).

```cpp 
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";

void setup() {
  Serial.begin(115200);
  
  // Conexión a la red WiFi
  WiFi.begin(ssid, password);
  
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println(" Conectado!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {  // Asegurarse de que el ESP32 esté conectado
    HTTPClient http;
    
    // Hacer una solicitud GET a un servidor
    http.begin("http://jsonplaceholder.typicode.com/posts/1");  // URL de prueba
    int httpCode = http.GET();  // Ejecutar la solicitud

    if (httpCode > 0) {  // Comprobar el código de respuesta
      String payload = http.getString();  // Obtener la respuesta
      Serial.println("Respuesta recibida:");
      Serial.println(payload);
    } else {
      Serial.println("Error en la solicitud");
    }

    http.end();  // Finalizar la conexión
  }

  delay(10000);  // Realizar una nueva solicitud cada 10 segundos
}
```  
- Resultado esperado: El ESP32 se conectará a una red WiFi y realizará una solicitud HTTP a un servidor web, imprimiendo la respuesta en el monitor serie.

3. **ESP32 en Modo Mixto (Access Point + Cliente)**

En este modo, el ESP32 actúa como un cliente conectado a una red WiFi y también como un punto de acceso simultáneo.   

```cpp

#include <WiFi.h>

// Configuración de AP
const char* ap_ssid = "ESP32_AP";
const char* ap_password = "12345678";

// Configuración de Cliente WiFi
const char* client_ssid = "your_SSID";
const char* client_password = "your_PASSWORD";

void setup() {
  Serial.begin(115200);

  // Configurar el ESP32 como Cliente WiFi
  WiFi.begin(client_ssid, client_password);
  Serial.print("Conectando a WiFi como cliente");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Conectado a WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Configurar el ESP32 como Access Point
  WiFi.softAP(ap_ssid, ap_password);
  Serial.println("Access Point creado");
  Serial.print("IP Address del AP: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // En este ejemplo, simplemente estamos manteniendo ambos modos activos
  // Puedes agregar funcionalidad para manejar conexiones entrantes al AP o hacer solicitudes desde el cliente WiFi
  delay(10000);
}


```  

- Resultado esperado: El ESP32 se conectará a la red WiFi como cliente y al mismo tiempo ofrecerá un punto de acceso llamado "ESP32_AP". Puedes conectarte al AP mientras el ESP32 sigue recibiendo datos desde la red WiFi.