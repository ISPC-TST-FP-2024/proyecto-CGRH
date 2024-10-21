# Manual de Verificación de Conexión de Módulos en ESP32


1. ## Objetivos del Proceso de Verificación

   - Asegurar la correcta conexión física y lógica de los módulos de comunicación al ESP32.
   - Comprobar la correcta transmisión y recepción de datos entre el ESP32 y los módulos.
   - Garantizar que los pines y las configuraciones de hardware sean correctas.  

---    

2. ## Requisitos Previos

- Herramientas de desarrollo: PlatformIO y Visual Studio Code.
- ESP32 con los módulos de comunicación correspondientes (WiFi, Bluetooth, etc.).
- Acceso a una red WiFi para las pruebas.  

---

3. ## Subtareas/Pasos de Verificación  


Paso 1: Identificar los pines de conexión para los módulos en la placa ESP32

    Consulta la hoja de datos del ESP32 para verificar los pines de conexión (GPIO) específicos para cada módulo.
    Asegúrate de que los pines seleccionados no interfieran con otros módulos o funciones de la placa.

Paso 2: Conectar físicamente los módulos de comunicación al ESP32

    Conecta cada módulo de comunicación (WiFi, Bluetooth, etc.) al ESP32 según el esquema de pines.
    Revisa las conexiones físicas para confirmar que estén seguras y que los cables no estén dañados.

Paso 3: Configurar los pines en el código de inicialización del microcontrolador

    Inicia una nueva sesión en PlatformIO.

    Configura los pines y credenciales de conexión WiFi en el código de tu ESP32, como en el siguiente ejemplo:

```cpp
const char* ssid = "nombre_red";
const char* password = "contraseña_red";

```
Configura el ESP32 como punto de acceso y cliente WiFi, y define las direcciones IP de los dispositivos de destino para realizar pruebas de conexión.

Paso 4: Realizar una prueba de comunicación básica entre el ESP32 y los módulos

- Sube el código al ESP32 y abre el monitor serie para observar el proceso de conexión.

- Verifica que el ESP32 se conecte correctamente a la red WiFi y que establezca una red de punto de acceso, si es necesario.

- Utiliza la función pingAndPrint para probar la conectividad con los dispositivos de destino mediante las direcciones IP configuradas.
```cpp
    void pingAndPrint(const IPAddress& ip) {
    WiFiClient client;
    if (client.connect(ip, echoPort)) {
        Serial.printf("Conexión a %s exitosa\n", ip.toString().c_str());
        client.stop();
    } else {
        Serial.printf("Conexión a %s fallida\n", ip.toString().c_str());
    }
}  
```

Paso 5: Verificar y corregir errores de conexión, si es necesario

Si el ESP32 no se conecta o muestra errores, verifica:
 - Las credenciales de la red WiFi.
 - La configuración de pines y la conexión física de los módulos.
 - La configuración de las IPs de destino.
Realiza ajustes en el código o en las conexiones físicas según sea necesario y repite las pruebas hasta obtener una conexión exitosa.

  
--- 

4. ## Pruebas de Comunicación

Realiza pruebas adicionales para verificar la transmisión de datos mediante diferentes protocolos, como MQTT, HTTP o TCP. Registra los resultados de cada prueba y, si hay errores, toma notas detalladas para una revisión posterior.