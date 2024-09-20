# Tecnicatura Superior en Telecomunicaciones
## Profesores: Gonzalo Vera, Jorge Morales, Dante Violi  

## Informacion General

*** Módulos de comunicación configurados y conectados al ESP32, protocolos de comunicación (WiFi, Bluetooth) configurados, pruebas iniciales de comunicación realizadas, documentación de la configuración de comunicación y resultados de pruebas. ***  

## Módulos de Comunicación Configurados y Conectados al ESP32.

### Hardware Utilizado:
- ESP32: Este microcontrolador tiene conectividad Wi-Fi y Bluetooth, lo que lo hace ideal para la comunicación inalámbrica.
- LED: Conectado al pin GPIO2 del ESP32 , con su resistencia adecuada de 220Ω.
### Esquema de Conexión:
esta conectado el cátodo del LED a GND y el ánodo al pin GPIO2 del ESP32 con una resistencia.

## Protocolos de Comunicación (Bluetooth) Configurados

### Protocolo Utilizado:
Bluetooth Classic (Serial Port Profile): Permite comunicación serial bidireccional entre el ESP32 y un dispositivo móvil.

### Librería Utilizada:
BluetoothSerial: Esta librería simplifica el manejo del Bluetooth en el ESP32, emulando una comunicación serial.

## Pruebas Iniciales de Comunicacion Realizadas
### Prueba 1: Conexión Bluetooth
#### Procedimiento:

Emparejar el ESP32 con el celular usando la app Serial Bluetooth Terminal.
Enviar caracteres desde la app al ESP32 y verificar la respuesta en el Monitor Serie del IDE Vs code.

#### Resultados:

El ESP32 recibe correctamente los caracteres enviados (1 y 0)
Los mensajes "LED encendido" y "LED apagado" aparecen en el Monitor Serie cuando el comando respectivos.

Prueba 2: Control del LED

#### Procedimiento:

Al enviar 1 desde el celular, el LED debe encenderse.
Al enviar 0, el LED debe apagarse.

### Resultados:

El LED se enciende y apaga correctamente en función de los comandos recibidos.

## Documentación de la Configuración de Comunicación y Resultados de Pruebas

### Configuración:

#### Configuración del Bluetooth:
Se utilizó el protocolo Serial Port Profile del Bluetooth para la comunicación.  

El ESP32 se configuró para que pueda usar la comunicación serial con el dispositivo móvil, utilizando la librería BluetoothSerial.  

#### Dispositivo móvil:
Se utilizó la aplicación Serial Bluetooth Terminal para enviar comandos al ESP32.
El dispositivo móvil se vinculo con el ESP32 bajo el nombre ESP32_LED.
### Resultados de Pruebas:

#### Conectividad Bluetooth: 
Se confirmó que el ESP32 se conecta correctamente a dispositivos móviles vía Bluetooth.
Control del LED: La comunicación bidireccional entre el ESP32 y el celular fue exitosa esto nos permite controlar el estado de un LED desde el celular mediante comando Bluetooth. 

#### Observaciones:
La velocidad de respuesta entre el envío del comando y la acción en el ESP32 fue inmediata, sin latencia perceptible.

## Actualizacion
20240916
Se actualizo Readme.
