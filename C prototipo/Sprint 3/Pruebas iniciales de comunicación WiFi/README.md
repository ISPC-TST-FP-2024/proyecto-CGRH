# H3TK 3 - Pruebas Iniciales de Comunicación WiFi con ESP32

Este proyecto tiene como objetivo realizar y documentar pruebas de la comunicación WiFi en un ESP32 utilizando PlatformIO con el framework de Arduino.

## Objetivos

- Realizar pruebas básicas de conexión y desconexión de la red WiFi.
- Validar la estabilidad de la conexión WiFi en diferentes entornos.
- Verificar la funcionalidad de escaneo de redes WiFi disponibles.
- Analizar el comportamiento de la memoria no volátil (NVS) en la reconexión automática.

## Tareas Realizadas

1. **Prueba de Conexión WiFi**  
   Conexión a una red WiFi local y verificación de la obtención de una dirección IP.

2. **Desconexión y Reconexión Manual**  
   Desconexión manual de la red WiFi y reconexión utilizando la funcionalidad de menú.

3. **Escaneo de Redes WiFi**  
   Validación de que las redes WiFi detectadas se muestran correctamente en la consola.

4. **Prueba de Reconexión Automática**  
   Verificación de la reconexión automática después de reiniciar el ESP32, validando que la información de conexión se guarda en la NVS (Non-Volatile Storage).

5. **Prueba de Estabilidad de Conexión**  
   Realización de pruebas para verificar caídas de la red y el comportamiento de la reconexión automática.

## Instrucciones para Realizar las Pruebas

Si deseas realizar alguna de las pruebas que se documentan en este proyecto, sigue los siguientes pasos:

1. Copia el código correspondiente al test que deseas probar.
2. Pega el código en el archivo `main.cpp` dentro de la carpeta `src` de tu proyecto PlatformIO.
3. Compila y sube el código a tu ESP32.
4. Observa los resultados en la consola serial para verificar el comportamiento del dispositivo durante las pruebas.

## Resultados de las Pruebas

Cada una de las pruebas realizadas se ha documentado con los resultados obtenidos en un informe aparte, que se puede consultar en el README.md de la carpeta `test` del proyecto.

---


## Test 1: Conexión a una Red WiFi y Obtención de IP

### Descripción

Esta prueba tiene como objetivo conectar el ESP32 a una red WiFi local y verificar si obtiene correctamente una dirección IP asignada por el router.

### Código

```cpp
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
```

### Configura las credenciales WiFi:

* **SSID:** Nombre de la red WiFi a la que quieres conectarte.  

* **Password:** Contraseña de la red WiFi.  

* Carga el código en el ESP32 a través de PlatformIO.

* Abre el monitor serie en PlatformIO para ver los mensajes del ESP32:

Se mostrará un mensaje indicando que el ESP32 está intentando conectarse a la red.  
Una vez conectado, se imprimirá la dirección IP asignada.  

### Resultados Esperados

* El ESP32 se conecta a la red WiFi especificada.  

* En el monitor serie, se verá un mensaje indicando el éxito de la conexión y la dirección IP local obtenida.  

### Observaciones

* Esta prueba debe ejecutarse en un entorno con una red WiFi disponible.  
* Si el ESP32 no se conecta, asegúrate de que las credenciales WiFi sean correctas y la señal sea lo suficientemente fuerte.

---

## Test 2: Desconexión y Reconexión Manual del WiFi

### Descripción
En esta prueba se implementa un menú interactivo en el monitor serie que permite al usuario conectar, desconectar y verificar el estado de la conexión WiFi manualmente.

### Código

```cpp
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
```
---
### Configura las credenciales WiFi:

* **SSID:** Nombre de la red WiFi a la que quieres conectarte.  

* **Password:** Contraseña de la red WiFi.  

* Carga el código en el ESP32 a través de PlatformIO.

* Abre el monitor serie en PlatformIO y verás un menú con tres opciones:

**1: Conectar a la red WiFi.**  
**2: Desconectar de la red WiFi.**  
**3: Mostrar el estado de la conexión (conectado o desconectado).**  

Escribe el número de la opción que desees realizar y presiona Enter para ejecutar la acción.

### Resultados Esperados

**Conectar a WiFi:** El ESP32 intenta conectarse a la red WiFi y muestra la dirección IP si se conecta correctamente.  

**Desconectar WiFi:** El ESP32 se desconecta de la red WiFi.  

**Estado de la Conexión:** Muestra si el ESP32 está conectado o desconectado de la red.  

### Observaciones
Esta prueba es útil para interactuar manualmente con el estado de la conexión WiFi del ESP32 sin tener que reiniciar el dispositivo.

---

## Test 3: Escaneo de Redes WiFi y Visualización en Consola

### Descripción

Este test realiza un escaneo de las redes WiFi disponibles y muestra en la consola el nombre (SSID), la potencia de la señal (RSSI), el canal y si la red está protegida (encriptada) o no.

### Código

```cpp
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
```
### Pasos
* Carga el código en el ESP32 a través de PlatformIO.

* Abre el monitor serie en PlatformIO para observar los resultados del escaneo.

* El ESP32 iniciará un escaneo de redes WiFi disponibles y mostrará:

**El nombre de cada red (SSID).**  
**La potencia de la señal en dBm (RSSI).**  
**El canal de la red.**  
**Si la red está encriptada o no.**  

### Resultados Esperados

* El ESP32 detectará y listará las redes WiFi disponibles en el entorno.  

* Cada red mostrará su nombre (SSID), la potencia de su señal, el canal y si la red está encriptada.  

### Observaciones

Esta prueba es útil para obtener información sobre las redes WiFi cercanas y su estado, ideal para evaluar la calidad de la señal y la seguridad de las redes disponibles.  
El escaneo se realiza una vez en el setup, por lo que no es necesario interactuar con el código después de la carga.

---

## Test 4: Reconexión Automática después de Reiniciar (Validación en NVS)

### Descripción
Este test valida que el ESP32 pueda reconectarse automáticamente a una red WiFi después de ser reiniciado, utilizando las credenciales previamente almacenadas en la memoria no volátil (NVS).

### Código

```cpp
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
```

### Pasos

* Carga el código en el ESP32 a través de PlatformIO.

* Observa en el monitor serie que el ESP32 se conecta a la red WiFi y muestra la dirección IP asignada.

* Reinicia el ESP32 (presiona el botón de reset o usa la opción en PlatformIO).

* Abre nuevamente el monitor serie para verificar que el ESP32 se reconecta automáticamente a la red utilizando las credenciales almacenadas en NVS (sin necesidad de volver a ingresarlas).

### Resultados Esperados

* El ESP32 se conectará a la red WiFi y mostrará la dirección IP en el monitor serie.  

* Después de reiniciar, el ESP32 se reconectará automáticamente a la red WiFi sin necesidad de ingresar nuevamente las credenciales.  

### Observaciones  

Este test es útil para verificar la capacidad del ESP32 de almacenar las credenciales en la NVS (memoria no volátil), lo que permite una reconexión automática tras un reinicio.  
Si el ESP32 no se reconecta después de reiniciar, asegúrate de que las credenciales sean correctas y que la red WiFi esté disponible.

---

## Test 5: Pruebas de Estabilidad de la Conexión WiFi

### Descripción
Este test monitorea la estabilidad de la conexión WiFi en el ESP32, verificando periódicamente si la red sigue conectada. Si se detecta una caída de la conexión, el ESP32 intenta reconectarse automáticamente.

### Código

```cpp
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
```
### Pasos  

### Configura las credenciales WiFi:

- SSID: Nombre de la red WiFi a la que quieres conectarte.  

- Password: Contraseña de la red WiFi.

- Carga el código en el ESP32 a través de PlatformIO.

- Abre el monitor serie en PlatformIO para observar el estado de la conexión WiFi:

**Se muestra el estado de la conexión cada 10 segundos.**  

**Si la conexión WiFi se pierde, el ESP32 intentará reconectarse automáticamente.**  

### Resultados Esperados
- Al inicio, el ESP32 se conectará a la red WiFi y mostrará la dirección IP.
- Cada 10 segundos, el ESP32 verifica el estado de la conexión.
- Si la conexión se pierde, intentará reconectar hasta un máximo de 5 intentos. Si tiene éxito, se mostrará la nueva dirección IP, y si falla, se indicará que no se pudo reconectar.  

### Observaciones
Este test es útil para verificar la estabilidad de la conexión WiFi y cómo el ESP32 maneja las caídas de red.  
Si el ESP32 no puede reconectarse después de una caída, asegúrate de que la red WiFi siga disponible y que las credenciales sean correctas.

## Conclusión

Estas pruebas permiten evaluar diferentes aspectos de la conectividad WiFi utilizando el ESP32, verificando la estabilidad, reconexión automática y manejo de la red. A lo largo de los cinco tests, hemos explorado:

1. La conexión básica a una red WiFi y la obtención de una dirección IP.
2. La posibilidad de conectar y desconectar manualmente de una red WiFi mediante un menú interactivo.
3. El escaneo de redes WiFi cercanas y la visualización de su información en la consola.
4. La capacidad del ESP32 para reconectarse automáticamente tras un reinicio, utilizando las credenciales almacenadas en la memoria no volátil (NVS).
5. Pruebas de estabilidad de la conexión, detectando caídas y gestionando la reconexión automática.

---
¡Gracias por revisar este proyecto!