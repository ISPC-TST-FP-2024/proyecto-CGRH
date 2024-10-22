# Tecnicatura Superior en Telecomunicaciones
### Profesores: Gonzalo Vera, Jorge Morales, Dante Violi  

## Informacion General

***La carpeta contiene toda la información relacionada con los prototipos de los sensores y sus respectivas simulaciones. En esta carpeta se encuentran los datasheets de cada sensor, las conexiones implementadas, así como el proyecto de PlatformIO para el desarrollo y programación del sistema. Además, se incluyen los archivos de simulación en Proteus para cuando no se pueda simular con PlatformIO , acompañados de las conclusiones obtenidas a partir de estas pruebas, los datos registrados, los valores medidos y si se puede un video demostrativo que muestra el funcionamiento del sistema y cómo se emplea en la práctica.***  

## Módulos de Comunicación LoRa SX1278 Configurados y Conectado al ESP32

### Hardware Utilizado:
- ESP32: Para controlar el módulo LoRa.
- Módulos LoRa SX1278: Para la comunicación inalámbrica a larga distancia.

### Esquema de Conexión (ESP32 con SX1278):
Los pines más comunes para conectar el SX1278 al ESP32 son:

VCC       3.3V  
GND	    GND	      
MISO    GPIO19    
MOSI    GPIO27  
SCK     GPIO5     
NSS     GPIO18  
RST     GPIO14  
DIO0    GPIO26  
Esta conexion es igual en ambos ESP32.  

### Protocolos de Comunicación Configurados.
Protocolo Utilizado:

LoRa (Long Range): Este protocolo nos permite la comunicaciones de largo alcance usando la modulación LoRa.

### Librería Utilizada:

LoRa Library: Esta librería nos permite manejar fácilmente la comunicación entre dispositivos LoRa.

## Pruebas Iniciales de Comunicación Realizadas

### Prueba 1: Transmisión y Recepción de Datos

Procedimiento:

Un ESP32 se configura como transmisor y el otro como receptor.
Se transmite un mensaje ("Hola desde el Transmisor!") cada 5 segundos desde el nodo transmisor.
El nodo receptor escucha continuamente y muestra el mensaje en el Monitor Serie.

Resultados:
El nodo receptor recibe los mensajes enviados y los imprime correctamente en el Monitor Serie.

Prueba 2: Distancia de Comunicación
Procedimiento:
Se prueba la comunicación entre los dos módulos a diferentes distancias para verificar hay que verificar el alcance.

Resultados:
Los módulos SX1278 lograron comunicación exitosa en un rango de varios cientos de metros en campo abierto.

## Documentación de la Configuración de Comunicación y Resultados de Pruebas
### Configuración:

#### Configuración del LoRa:

Se utilizó la librería LoRa.h para manejar la comunicación entre los dos módulos SX1278.
Los pines SS, RST y DIO0 se asignaron según el esquema de conexión descrito.
Se utilizó la frecuencia de 433 MHz para la transmisión, que es común para los módulos SX1278.

#### Dispositivos:

Dos ESP32 configurados: uno como transmisor y otro como receptor.  

Los módulos LoRa se conectaron de acuerdo al esquema de pines sugerido.
#### Resultados de Pruebas:

- Comunicación: Se confirmó la comunicación bidireccional entre dos módulos SX1278, con mensajes enviados y recibidos correctamente.
- Alcance: Se lograron transmisiones exitosas a larga distancia (varios cientos de metros) en campo abierto, demostrando la capacidad de largo alcance de LoRa.
- Estabilidad: La comunicación fue estable en distancias cortas y largas, sin pérdida de datos durante las pruebas iniciales.

## Actualizacion
20240916
Se actualizo Readme.
