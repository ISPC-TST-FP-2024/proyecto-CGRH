# Sistema de Cultivo Vertical Inteligente con Comunicación entre Nodos

## Resumen 
Este informe presenta el desarrollo de un sistema de cultivo vertical inteligente, que consta de tres nodos interconectados. Cada nodo mide variables ambientales y las transmite al nodo central, el cual almacena la información en una base de datos y controla dispositivos como bombas de agua y luces de crecimiento. Se utilizan diferentes tecnologías de comunicación (Bluetooth y LoRa) para la transmisión de los datos en función de la distancia entre nodos.

## Introducción
El proyecto tiene como objetivo monitorear y controlar de manera automática un sistema de cultivo vertical mediante la recopilación de datos ambientales (como temperatura, humedad, luz y humedad del suelo) y la automatización del riego y la iluminación en función de estos parámetros. El sistema está compuesto por tres nodos que se comunican entre sí para gestionar las condiciones del cultivo.

## Objetivos del Proyecto
Monitorear en tiempo real variables ambientales como temperatura, humedad y luz. Para 
controlar dispositivos de riego y luces basados en condiciones ambientales.
Almacenar datos en una base de datos para análisis posteriores.

## Descripción General de los Nodos
El sistema está diseñado con una arquitectura de red en la que los nodos 2 y 3 recolectan datos y los envían al nodo 1 utilizando diferentes tecnologías de comunicación. El nodo 1 es el nodo central que actúa como un puente de control, consolidando los datos y enviándolos a una base de datos externa mediante Wi-Fi. También activa la bomba de agua y las luces según las condiciones del ambiente.

### Hardware Utilizado

Nodo 1 (Nodo Central):

- ESP32 WROOM de 38 pines (módulo principal con Wi-Fi y Bluetooth integrados).
- Display IPS 0.96" 80x160 con controlador ST7735 (pantalla para mostrar los datos).
- Sensor de humedad y temperatura AHT10 I2C (para medir la temperatura y humedad del ambiente).
- Módulo LoRa SX1278 (para recibir datos de largo alcance desde el Nodo 3).
- Relé de 2 canales optoacoplado de 5V (para controlar la bomba de agua y las luces).
- Bomba de agua sumergible de 120 L/h.
- LED COB de 50W Full Spectrum para crecimiento indoor.
- HC-SR04

Nodo 2 (Bluetooth):

- ESP32 WROOM de 38 pines (con Bluetooth integrado).
- Display IPS 0.96" 80x160 con controlador ST7735 (pantalla para mostrar los datos).
- Sensor de humedad y temperatura AHT10 I2C.
- Sensor de humedad de suelo resistivo.
- Sensor de luz LDR (Fotoresistor).
- Relé de 2 canales optoacoplado de 5V (para el control de la bomba y luces).
- Bomba de agua sumergible de 120 L/h.
- HC-SR04
- LED COB de 50W Full Spectrum para crecimiento indoor.

Nodo 3 (LoRa):

- ESP32 WROOM de 38 pines.
- Sensor de humedad y temperatura AHT10 I2C.
- Sensor de humedad de suelo capacitivo.
- Sensor de luz LDR (Fotoresistor).
- Módulo LoRa SX1278 (para comunicaciones de largo alcance).
- Relé de 2 canales optoacoplado de 5V (para el control de la bomba y luces).
- Bomba de agua sumergible de 120 L/h.
- HC-SR04
- LED COB de 50W Full Spectrum para crecimiento indoor.

## Desarrollo de los Nodos

### Envío de Información al Nodo Central
- Nodo 2 (Bluetooth): Recoge la información del sensor de humedad del suelo, el sensor de temperatura y el sensor de luz, y envía estos datos al nodo 1 a través de Bluetooth.
- Nodo 3 (LoRa): Similar al nodo 2, este nodo recoge los mismos datos, pero los transmite al nodo 1 usando LoRa, debido a la mayor distancia entre los nodos.

### Comunicación a través de Bluetooth y LoRa
El sistema utiliza Bluetooth para la comunicación de corto alcance entre el nodo 2 y el nodo central (nodo 1), mientras que utiliza LoRa para la comunicación de largo alcance entre el nodo 3 y el nodo 1, asegurando una transmisión robusta y de bajo consumo.

## Base de Datos

### Información Enviada al Nodo Central y Base de Datos
El nodo 1 recibe la siguiente información de los nodos 2 y 3, y luego la envía a una base de datos remota a través de Wi-Fi:

- Temperatura ambiente (en grados Celsius).
- Humedad relativa del aire (en %).
- Humedad del suelo (en %).
- Nivel de luz (medido por el LDR).
- Estado de los dispositivos controlados (bomba y luces).

### Estructura de la Base de Datos
La base de datos almacena cada lectura junto con el ID del nodo que envió la información y una marca de tiempo. Esto permite registrar los datos históricos para realizar análisis a largo plazo, optimizando el control del sistema de cultivo.

## Actividad de los Nodos
- Nodo 2 (Bluetooth): Mide las condiciones del ambiente (humedad, temperatura y luz) y envía los datos al nodo 1. El nodo también controla dispositivos locales (bomba de agua y luces) según los datos que recoge.
- Nodo 3 (LoRa): Funciona igual que el nodo 2, pero utiliza el protocolo LoRa para enviar los datos al nodo central debido a su ubicación más alejada. Este nodo también controla la bomba y las luces en su área específica.
- Nodo 1 (Nodo Central): Recibe y procesa los datos de los nodos 2 y 3, los muestra en la pantalla IPS y los envía a una base de datos remota mediante Wi-Fi. También controla los dispositivos (bomba de agua y luces) basándose en las condiciones generales del sistema.

## Librerías Utilizadas

### Descripción de Librerías
- WiFi.h: Para habilitar la conectividad Wi-Fi en el nodo 1 y enviar los datos a la base de datos.
- BluetoothSerial.h: Permite la comunicación entre los nodos 2 y 1 mediante Bluetooth.
- LoRa.h: Se utiliza en el nodo 3 para la transmisión de largo alcance hacia el nodo 1.
- Adafruit_GFX.h y Adafruit_ST7735.h: Controlan la pantalla IPS para mostrar los datos en el nodo 1.
- DHTesp.h y AHT10.h: Para la lectura de los sensores de temperatura y humedad AHT10.
- CapacitiveSoilMoistureSensor.h: Para la lectura del sensor de humedad de suelo capacitivo.

### Funcion

- BluetoothSerial.read() y LoRa.receive(): Reciben los datos de los nodos 2 y 3, respectivamente.
- WiFiClient.post(): Se usa para enviar los datos a la base de datos central.
- display.drawString(): Para mostrar información en la pantalla IPS del nodo 1.
- AHT10.getTemperature() y getHumidity(): Para la lectura de temperatura y humedad desde el sensor AHT10.
- CapacitiveSoilMoistureSensor.read(): Para medir la humedad del suelo en el nodo 3.

## Análisis y Resultados
El sistema ha demostrado ser efectivo para monitorear el ambiente de un cultivo vertical, transmitiendo los datos desde los nodos 2 y 3 hacia el nodo central utilizando las tecnologías de Bluetooth y LoRa. La información es almacenada correctamente en una base de datos remota, lo que permite análisis posteriores. El control de la bomba de agua y las luces ha funcionado de manera óptima según las condiciones del ambiente.

## Conclusiones y Mejoras Futuras
El proyecto ha logrado cumplir con los objetivos principales, permitiendo un control automatizado y eficiente de un sistema de cultivo vertical. Para futuras mejoras, se podría considerar la inclusión de un sistema de control remoto mediante una aplicación móvil, así como la incorporación de paneles solares para alimentar los nodos de forma autónoma.

## Consumo Energético del Proyecto

El consumo energético es un aspecto inportante para el correcto funcionamiento de los nodos del sistema. los consumos estimados de los componentes más importantes en cada nodo, junto con una estimación del consumo diario total.

### Consumo Estimado por Nodo:
#### Nodo Central (ESP32 + Display, Sensores, Módulo LoRa, Relés y Bomba de Agua):
- Consumo promedio en modo activo: **1.1 A**
- Consumo promedio en modo de bajo consumo: **0.5 A**

#### Nodo Bluetooth (ESP32 + Sensores, Display, Relés y Bomba de Agua):
- Consumo promedio en modo activo: **1 A**
- Consumo promedio en modo de bajo consumo: **0.4 A**

#### Nodo LoRa (ESP32 + Sensores, Display, Módulo LoRa, Relés y Bomba de Agua):
- Consumo promedio en modo activo: **1.1 A**
- Consumo promedio en modo de bajo consumo: **0.5 A**

### Consumo Diario Estimado
Si se asume que los nodos están en modo activo durante 6 horas al día y en modo de bajo consumo el resto del tiempo, el consumo diario por nodo sería:

- Nodo Central: 6.6 Ah en modo activo + 9 Ah en modo bajo consumo = **15.6 Ah/día**
- Nodo Bluetooth: 6 Ah en modo activo + 7.2 Ah en modo bajo consumo = **13.2 Ah/día**
- Nodo LoRa: 6.6 Ah en modo activo + 9 Ah en modo bajo consumo = **15.6 Ah/día**

### Importancia de la Optimización del Consumo
La optimización del consumo energético es fundamental para maximizar la eficiencia del sistema, especialmente si el proyecto se orienta a aplicaciones de bajo mantenimiento o con fuentes de energía limitada como sistemas solares. Reducir el consumo puede aumentar la autonomía del sistema y reducir costos operativos a largo plazo.

# Análisis de proyecto y mejoras

## Nodo Central (Nodo 1)

### Pérdida de datos por fallos de comunicación
El nodo central puede perder datos cuando los nodos secundarios (Nodo 2 y Nodo 3) no pueden comunicarse debido a interferencias en la señal LoRa, falta de conectividad o condiciones de señal débil. La pérdida de datos es crítica cuando se requiere un monitoreo constante de variables o eventos.

**Mejora:** Implementar un buffer local en el nodo central para almacenar temporalmente los datos provenientes de los nodos secundarios. Si hay una interrupción en la transmisión, los datos se almacenan en el buffer hasta que la conexión se restablezca, momento en el cual se pueden reanudar las transmisiones y reenviar los datos almacenados.

###  Falta de manejo de errores en la transmisión de datos
Actualmente, si se produce un error durante la transmisión de datos entre los nodos (por ejemplo, una pérdida de paquetes), no hay un mecanismo para detectar y corregir este error. Esto puede resultar en datos incompletos o incorrectos.

**Mejora:** Implementar un sistema de detección y corrección de errores utilizando checksums u otros algoritmos de verificación de integridad de datos. Si se detecta un error en los datos recibidos, se debe solicitar una retransmisión del paquete afectado, garantizando que la información almacenada y procesada sea precisa.
###  Desincronización de tiempos entre nodos
Los nodos secundarios pueden no estar sincronizados en cuanto a la hora o el tiempo de toma de muestras, lo que causa inconsistencia en las lecturas registradas.

**Mejora:** Implementar una sincronización temporal utilizando el reloj del nodo central (RTC o sincronización NTP). El nodo central puede enviar señales de sincronización periódicas a los nodos secundarios, asegurando que las lecturas de los sensores en todos los nodos se realicen en intervalos consistentes.

###  Falta de un mecanismo de actualización remota
Cada vez que se necesita actualizar el firmware del nodo central o los nodos secundarios, se requiere realizar la actualización manualmente, lo que puede ser ineficiente y propenso a errores si hay múltiples dispositivos.

**Mejora:** Implementar un sistema de actualización de firmware OTA (Over-The-Air). De esta manera, las actualizaciones del código o del firmware se pueden realizar de manera remota, utilizando una conexión Wi-Fi o LoRa, eliminando la necesidad de intervención física en cada dispositivo.

###   Pérdida de datos por fallo en la conexión Wi-Fi
El nodo central depende de la conectividad Wi-Fi para enviar los datos recopilados a un servidor o base de datos externa. Si la conexión Wi-Fi falla o está fuera de servicio temporalmente, se pueden perder los datos capturados en ese periodo.

**Mejora:** Implementar un sistema de almacenamiento temporal en el nodo central, utilizando una memoria local (como una tarjeta SD o la memoria flash del ESP32) para guardar los datos localmente. Una vez que la conexión Wi-Fi se restablezca, los datos almacenados pueden ser enviados al servidor, asegurando que no se pierdan.

### Altos consumos de energía durante el procesamiento continuo
El nodo central consume energía constantemente al estar activo todo el tiempo, procesando datos o esperando señales de los nodos secundarios. Esto puede ser problemático si el sistema está alimentado por baterías.

**Mejora:** Implementar modos de bajo consumo en el nodo central, como el modo deep sleep del ESP32. El nodo central puede entrar en este modo cuando no esté procesando datos activamente o cuando no se esperen señales de los nodos secundarios, ahorrando energía y extendiendo la duración de la batería.

###  Interferencias con otros dispositivos Bluetooth
Si el nodo central está utilizando una conexión Bluetooth para comunicar datos a otro dispositivo (por ejemplo, una aplicación móvil), podría haber interferencias con otros dispositivos Bluetooth cercanos, afectando la calidad y la velocidad de la transmisión.

**Mejora:** Implementar un mecanismo de cambio de canal o frecuencia para evitar interferencias con otros dispositivos Bluetooth. Al usar canales menos congestionados, el nodo central puede mejorar la estabilidad y la velocidad de la conexión.

###  No hay control sobre el estado de las baterías de los nodos
Los nodos secundarios pueden estar operando con baterías, y si una batería se descarga, podría interrumpir la comunicación o los datos enviados al nodo central. Actualmente, no hay un sistema que monitorice el estado de las baterías.

**Mejora:** Implementar un sistema de monitoreo de voltaje en los nodos secundarios. El nodo central puede recibir información sobre el estado de la batería y generar alertas si la batería está baja, permitiendo una intervención antes de que el nodo falle.

## Nodos Secundarios (Nodo 2 y Nodo 3)

### Pérdida de conexión intermitente con el nodo central
Los nodos secundarios pueden perder conexión con el nodo central debido a la interferencia en la señal LoRa o a la distancia entre los nodos. Esto resulta en pérdida de datos o en la incapacidad de enviar lecturas críticas.

**Mejora:** Implementar un sistema de reconexión automática que detecte cuándo se ha perdido la conexión y reintente automáticamente hasta restablecerla. Además, los datos deben ser almacenados en un buffer local hasta que la conexión se reanude, momento en el cual se pueden transmitir los datos almacenados.

###  Consumo de energía elevado durante la operación continua
Los nodos secundarios pueden estar constantemente activos, monitoreando y transmitiendo datos al nodo central, lo que genera un alto consumo de energía, especialmente si están alimentados por baterías.

**Mejora:** Implementar modos de bajo consumo en los nodos secundarios, utilizando el modo deep sleep del ESP32 o del chip LoRa cuando no están transmitiendo activamente. Los nodos pueden despertar a intervalos específicos para tomar lecturas y enviar datos al nodo central, reduciendo así el consumo total de energía.

###   No hay un mecanismo para verificar si los datos transmitidos son correctos
Cuando los nodos secundarios envían datos al nodo central, no hay un sistema que verifique si los datos han llegado correctamente. Esto podría llevar a lecturas erróneas o datos incompletos.

**Mejora:** Implementar un sistema de verificación de integridad de datos en los nodos secundarios, utilizando checksums u otro mecanismo de validación. El nodo central puede solicitar una retransmisión si detecta que los datos han sido corrompidos.

###  Sincronización incorrecta de lecturas en los nodos
Los nodos secundarios pueden estar tomando lecturas en diferentes tiempos, lo que genera inconsistencia en los datos transmitidos al nodo central.

**Mejora:** Implementar un mecanismo de sincronización temporal en los nodos secundarios, utilizando el reloj del nodo central para enviar señales de sincronización periódicas. Esto asegurará que todos los nodos secundarios tomen lecturas al mismo tiempo.


##  Bibliografía y Referencias
Documentación oficial de ESP32 y LoRa.
Especificaciones técnicas de sensores AHT10 y LoRa SX1278.
