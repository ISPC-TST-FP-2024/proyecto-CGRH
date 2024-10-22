#  Sistema de Cultivo Vertical IoT con Comunicación Multinodo

Este proyecto utiliza tres nodos para monitorear y controlar un cultivo vertical, empleando sensores para medir la temperatura, humedad, luz, y el nivel de agua en el depósito.
Cada nodo tiene un **ID único** y utiliza diferentes métodos de comunicación para enviar la información al nodo principal.
La transmite a una base de datos en una Raspberry Pi a través de Wi-Fi. Las comunicaciones incluyen Bluetooth, LoRa, y una red Wi-Fi local.


## Nodo 3 (LoRa):

El Nodo 3 utiliza comunicación LoRa para enviar la información al nodo principal. Al igual que los otros nodos, incluye un ID único en cada mensaje, lo que permite que el nodo principal y la base de datos identifiquen de qué nodo provienen los datos.

### Uso:
- Muestra los datos en una pantalla.
- Envía los datos a una base de datos utilizando LoRa.
- Se encarga del control del sistema, como activar las luces y la bomba de agua, basándose en las condiciones ambientales.
### Comunicación:
- Envia por comunicacion LoRA, identificando la fuente de los datos mediante el ID único de cada nodo.
### Control:
- Controla la bomba de agua (usando un relé), las luces de crecimiento (usando otro relé), y monitoriza el nivel de agua.

# Biografía y Librerías Utilizadas
##  LoRa.h
**Descripción:** La librería LoRa.h proporciona una interfaz para comunicarse utilizando la tecnología de radio LoRa. LoRa (Long Range) es una tecnología de comunicación inalámbrica de baja potencia que es ideal para proyectos IoT donde se requiere transmitir datos a largas distancias.

 **Funcion:**
- **LoRa.begin():** Inicializa la comunicación LoRa en una frecuencia específica.
- **LoRa.beginPacket():** Inicia un paquete de datos para enviar.
- **LoRa.print() y LoRa.endPacket():** Envían el paquete al nodo receptor.
- **LLoRa.read():**L Lee el paquete recibido.
- **LLoRa.write():**L Envía datos a través de la red LoRa.  
**Fuente oficial:**   
la documentación oficial en GitHub:
https://github.com/sandeepmistry/arduino-LoRa 


## Adafruit_AHTX0.h
**Descripción:** La librería Adafruit_AHTX0 permite leer los valores de sensores de temperatura y humedad como el AHT10, que es un sensor de alta precisión que se comunica a través del protocolo I2C.

**Funcion:**
- **aht.begin():** Inicializa la comunicación I2C con el sensor.
- **aht.getEvent():** Obtiene los valores de temperatura y humedad del sensor.


## Adafruit_GFX.h y Adafruit_ST7735.h
**Descripción:** Adafruit_GFX es una librería que proporciona primitivas gráficas básicas (líneas, texto, formas) para pantallas, mientras que **Adafruit_ST7735** está diseñada para controlar pantallas TFT como la de 0.96 pulgadas utilizada en el proyecto.
**Funciones clave:**  
- **tft.setCursor(), tft.setTextColor(), tft.setTextSize():** Permiten manipular el texto mostrado en la pantalla.
- **tft.fillScreen():** Limpia la pantalla y permite actualizarla con nueva información.


## Wire.h
**Descripción:** Librería estándar de Arduino que facilita la comunicación I2C entre el microcontrolador y dispositivos periféricos, como sensores de temperatura, humedad o pantallas.  

**Funcion:**
-  **Wire.begin():** Inicializa el bus I2C.
- **Wire.requestFrom(address, quantity):** Solicita datos del dispositivo I2C con la dirección especificada.
- **Wire.write():** Envía datos al dispositivo conectado mediante I2C.
- **Wire.read():** Lee datos del dispositivo conectado.


## SPI.h
**Descripción:** La librería SPI.h permite la comunicación con dispositivos que usan el protocolo SPI (Serial Peripheral Interface), como la pantalla ST7735.

**Funcion:**
- **SPI.begin():** Inicializa el bus SPI.
- **SPI.transfer(data):** Envía y recibe datos a través de SPI.

## BluetoothSerial.h
**Descripción:** Esta librería facilita la comunicación entre el ESP32 y otros dispositivos a través de Bluetooth Serial. Permite que el ESP32 actúe como un puerto serie Bluetooth para intercambiar datos.

**Funcion:**
- **SerialBT.begin():** Inicializa el módulo Bluetooth en el ESP32.
- **SerialBT.write() y SerialBT.read():** Envían y reciben datos mediante Bluetooth.  

**Fuente oficial:**  
La documentación de esta librería se encuentra en el repositorio oficial:
https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial



## DHTesp.h
**Descripción:**
Esta librería se usa para interactuar con los sensores DHT (DHT11, DHT22) de temperatura y humedad. se utiliza para capturar los datos de temperatura y humedad ambiente que luego se envían al nodo central.

**Funcion:**
- **dht.setup(pin, DHTesp::DHT22):** Inicializa el sensor en el pin especificado (usando el tipo de sensor, en este caso DHT22).
- **dht.getTemperature():** Obtiene la temperatura actual del sensor.
- **dht.getHumidity():** Obtiene la humedad relativa del sensor.

**Fuente oficial:**
el código fuente en GitHub:
https://github.com/beegee-tokyo/DHTesp

## Lectura de Sensores:

Cada nodo tiene sensores para medir la temperatura y humedad del ambiente, la humedad del suelo (tanto con sensores resistivos como capacitivos), la luz ambiental y el nivel de agua en el depósito de riego.
El Nodo  se encarga de controlar los relés que activan la bomba de agua y las luces, basándose en los valores medidos por estos sensores.

### Control de Relés:

- Si los sensores detectan que el nivel de agua es bajo, el sistema no activa la bomba y muestra un aviso en la pantalla.
- Las luces de crecimiento se activan o desactivan según el nivel de luz ambiental medido por el sensor LDR.

## Envío de Información a la Base de Datos:

Cada nodo incluye un ID único en el mensaje que envía, para que el nodo principal y la base de datos puedan identificar de qué nodo provienen los datos.
El nodo principal recolecta esta información, la muestra en una pantalla y luego la transmite a la base de datos a través de Wi-Fi.

### La información enviada incluye:
- Temperatura ambiente
- Humedad del ambiente
- Humedad del suelo (superior e inferior)
- Luz ambiente
- Nivel de agua en el depósito
- Estado de los relés (bomba de agua y luces)
- Configuración del Nodo Principal:

El nodo central permite elegir si va a recibir datos por Bluetooth, LoRa, o los dos. Esta configuración se realiza en un menú simple mostrado en la pantalla.

## Información Enviada a la Base de Datos
El nodo 3 enviará los siguientes datos a la base de datos al nodo Central, junto con el ID del nodo que originó la información:

- Temperatura ambiente (en °C)
- Humedad ambiente (en %)
- Humedad del suelo (superior e inferior) (en valores analógicos)
- Luz ambiental (en valores analógicos)
- Nivel de agua (en cm)
- Estado de los relés (encendido/apagado para la bomba de agua y las luces)
Esto permite almacenar las condiciones del cultivo, que puede ser usado para análisis y ajustes del sistema.

## Funcionanamiento y qué Información Envía.
Cada una de las librerías que hemos usado tiene un rol específico en la estructura de nuestro sistema IoT:

- **LoRa.h y SPI.h:** Se encarga de la comunicación LoRa entre los nodos y el nodo central. Es útil para largas distancias y baja potencia, garantiza que las lecturas de los sensores lleguen al nodo principal.

- **DHTesp.h:** Esta librería lee los datos de temperatura y humedad, del cultivo vertical.

- **Wire.h:** Facilita la comunicación con sensores y módulos a través de I2C, como las pantalla LCD o otros dispositivos que requieran esa interfaz I2C.

## Consumo Energético

### Nodo LoRa (Nodo 3)

- ESP32 WROOM 38 pines: ~240 mA
- Display IPS 0.96 Color 80x160 (ST7735): ~25 mA
- Sensor AHT10 (Humedad y Temperatura): ~0.2 mA
- Bomba Agua Sumergible (120l/h, 3-5V): ~350 mA (a 5V)
- Sensor de Humedad de Suelo (Resistivo): ~20 mA
- Sensor de Humedad de Suelo Capacitivo V1.2: ~10 mA
- Sensor de Luz con LDR (Fotoresistor): ~0.5 mA
- LED COB 50W Grow Indoor Full Spectrum: ~250 mA (controlado por relé)
- Relé de 2 Canales Optoacoplado: ~75 mA (cuando se activa)
- HC-SR04 (Sensor Ultrasonido): ~15 mA
- Módulo LoRa SX1278: ~120 mA (en transmisión)

#### Consumo estimado total del Nodo LoRA:

- Modo activo (todos los componentes funcionando): 1105 mA
- Modo reposo (sin bomba y relés activados): 505 mA