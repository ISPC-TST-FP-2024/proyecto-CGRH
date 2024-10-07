# Manual de Verificación de Conexión de Módulos en ESP32

## Objetivos del Proceso de Verificación

- Asegurar la correcta conexión física y lógica de los módulos de comunicación al ESP32.
- Comprobar la correcta transmisión y recepción de datos entre el ESP32 y los módulos.
- Garantizar que los pines y las configuraciones de hardware sean correctas.

---

## Requisitos Previos

- Herramientas de desarrollo: PlatformIO y Visual Studio Code.
- ESP32 con los módulos de comunicación correspondientes (WiFi, Bluetooth, etc.).
- Sensor AHT10 para medición de temperatura y humedad.

---

## Subtareas/Pasos de Verificación

### Paso 1: Identificar los pines de conexión para el AHT10 en la placa ESP32

- El sensor AHT10 se conecta a través del bus I2C. Generalmente, se utiliza:
  - **SDA** (Data) en GPIO 21.
  - **SCL** (Clock) en GPIO 22.

### Paso 2: Conectar físicamente el AHT10 al ESP32

- Conecta el pin **SDA** del AHT10 al pin **GPIO 21** del ESP32.
- Conecta el pin **SCL** del AHT10 al pin **GPIO 22** del ESP32.
- Conecta los pines de alimentación:
  - **VCC** a **3.3V**.
  - **GND** a **GND**.

### Paso 3: Programar el ESP32 para Bluetooth y lectura del AHT10

```cpp
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>
#include <BluetoothSerial.h>

Adafruit_AHTX0 aht; // Crea una instancia del sensor AHT10
BluetoothSerial SerialBT; // Instancia del Bluetooth

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_BT"); // Inicia el Bluetooth
  Serial.println("Bluetooth iniciado");

  if (!aht.begin()) { // Inicializa el sensor
    SerialBT.println("No se pudo encontrar el sensor AHT10");
    while (1) delay(10);
  }
  SerialBT.println("Sensor AHT10 iniciado.");
}

void loop() {
  sensors_event_t humidity, temperature;
  aht.getEvent(&temperature, &humidity); // Lee los datos del sensor

  // Envía los datos por Bluetooth
  SerialBT.print(F("Temperatura: "));
  SerialBT.print(temperature.temperature);
  SerialBT.print(F(" °C, Humedad: "));
  SerialBT.print(humidity.relative_humidity);
  SerialBT.println(F(" %"));

  delay(5000); // Espera 5 segundos antes de volver a leer
}
```

### Paso 4: Subir el código al ESP32

- Carga el código en el ESP32 utilizando PlatformIO.
- Abre el monitor serie para ver la salida inicial.

### Paso 5: Verificar la comunicación por Bluetooth

- Conecta tu dispositivo (móvil, tablet, etc.) al Bluetooth del ESP32, cuyo nombre es "ESP32_BT".
-  Verifica que recibas los datos de temperatura y humedad enviados desde el ESP32 a través de Bluetooth
- se adjunta imagen de telefono android con la aplicacion "Serial Bluetooth Terminal"
![imagen BT](https://github.com/ISPC-TST-FP-2024/proyecto-CGRH/blob/main/C%20prototipo/Sprint%202/Prueba%20de%20comunicacion%20BT/img/delay%205s.jpg)
