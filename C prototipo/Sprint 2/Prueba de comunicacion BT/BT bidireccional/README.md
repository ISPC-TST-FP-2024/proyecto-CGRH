# Prueba de Comunicación Bluetooth - Sensor AHT10 y ESP32

## Objetivo

El objetivo de esta prueba es validar la funcionalidad de comunicación Bluetooth entre un ESP32 y un dispositivo externo. La prueba se enfoca en la capacidad del ESP32 para enviar datos de temperatura y humedad, obtenidos desde el sensor AHT10, mediante la comunicación Bluetooth.

## Descripción del Programa

Este programa utiliza la librería `Adafruit_AHTX0` para comunicarse con un sensor AHT10 y obtener datos de temperatura y humedad, y la librería `BluetoothSerial` para habilitar la comunicación Bluetooth en el ESP32.

El flujo de trabajo es el siguiente:

1. El ESP32 inicia la comunicación Bluetooth.
2. Se inicializa el sensor AHT10 y se verifica su conexión.
3. Se espera un comando desde el dispositivo Bluetooth conectado. Si se recibe el comando `'G'`, se leen los datos del sensor.
4. Los datos de temperatura y humedad se envían al dispositivo conectado a través de Bluetooth.

## Configuración del Hardware

- **ESP32**
- **Sensor AHT10** conectado al ESP32 a través de I2C
- **Dispositivo Bluetooth** para recibir los datos enviados por el ESP32.

### Esquema de Conexión

Conectar el sensor AHT10 al ESP32 utilizando los siguientes pines:

- **VCC** del AHT10 a **3.3V** del ESP32
- **GND** del AHT10 a **GND** del ESP32
- **SDA** del AHT10 a **GPIO 21** del ESP32
- **SCL** del AHT10 a **GPIO 22** del ESP32

<div style="text-align: center;">
  <img src="https://github.com/ISPC-TST-FP-2024/proyecto-CGRH/blob/main/C%20prototipo/Sprint%202/Prueba%20de%20comunicacion%20BT/img/IMG_20241006_175931.jpg" alt="imagen esp32" style="width: 70%;">
</div>

## Procedimiento de Prueba

1. **Preparación del ESP32:**

    - Subir el código al ESP32 utilizando PlatformIO o el IDE de Arduino.
    - Asegurarse de que el ESP32 está encendido y listo para comunicarse por Bluetooth.
2. **Inicio de la Comunicación Bluetooth:**

    - Conectar al ESP32 desde un dispositivo Bluetooth utilizando el nombre `"ESP32_BT"`.
    - Verificar que el ESP32 emite el mensaje "Bluetooth iniciado" y "Sensor AHT10 iniciado" en el monitor serial.
3. **Comprobación de Recepción de Comandos:**

    - Desde el dispositivo conectado, enviar el carácter `'G'` para solicitar datos.
    - Confirmar que el ESP32 recibe el comando y emite "Solicitando datos del sensor...".
4. **Validación de Datos:**

    - Verificar que el ESP32 lee correctamente los datos de temperatura y humedad del sensor AHT10.
    - Confirmar que los datos se envían al dispositivo conectado, visualizando una salida similar a:

        ```yaml

        Temperatura: 25.4 °C, Humedad: 40.2 %

        ```
5. **Prueba de Repetición:**

- Repetir el envío del comando `'G'` para verificar que el ESP32 sigue respondiendo adecuadamente y los datos se actualizan conforme a la lectura del sensor.

## Resultados Esperados

- El ESP32 se conecta correctamente vía Bluetooth.
- Al recibir el comando `'G'`, el ESP32 lee y envía los datos del sensor AHT10 de forma precisa.
- Los datos se muestran en el dispositivo Bluetooth conectado sin interrupciones ni errores.

<div style="text-align: center;">
  <img src="https://github.com/ISPC-TST-FP-2024/proyecto-CGRH/blob/main/C%20prototipo/Sprint%202/Prueba%20de%20comunicacion%20BT/img/bidireccional.jpg" alt="imagen bt" style="width: 70%;">
</div>

