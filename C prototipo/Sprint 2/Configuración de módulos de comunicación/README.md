# Tecnicatura Superior en Telecomunicaciones
### Profesores: Gonzalo Vera, Jorge Morales, Dante Violi  

## Investigaciones e Implementaciones en Tecnologías de Comunicación (Wi-Fi, LoRa, Bluetooth).

## Informacion General

***Esta carpeta contiene una colección de investigaciones y desarrollos realizados en torno a tres tecnologías de comunicación inalámbrica: Wi-Fi, LoRa, y Bluetooth. En este  proyecto, se han implementado diversas soluciones utilizando el ESP32 y el NodeMCU ESP8266, con el objetivo de lograr una comunicación eficiente y confiable entre dispositivos IoT. Cada una de las tecnologías exploradas en esta carpeta tiene su propia sección, donde se detallan los procedimientos seguidos para su configuración, pruebas realizadas, resultados obtenidos y la implementación final. Además, se incluye una conclusión general que compara las capacidades y casos de uso ideales de cada tecnología.***  

## Implementación de Comunicación mediante Wi-Fi

Descripción:
En esta sección se presenta la implementación de la comunicación mediante Wi-Fi usando el NodeMCU ESP8266. Se ha utilizado el protocolo HTTP para enviar y recibir datos desde un servidor remoto. El documento cubre desde la configuración inicial del módulo ESP8266 para conectarse a una red Wi-Fi, hasta las pruebas de envío de datos utilizando solicitudes HTTP POST.

Procedimientos Realizados:

Configuración de la conexión Wi-Fi en el ESP8266.
Envío de datos a un servidor web a través de HTTP.
Validación de la comunicación con respuestas del servidor.

Conclusión:

La comunicación mediante Wi-Fi es eficiente y permite el envío de grandes volúmenes de datos en tiempo real, lo que la convierte en una opción ideal para aplicaciones IoT en entornos con acceso a internet. Sin embargo, depende de la cobertura y estabilidad de la red Wi-Fi.

## Implementación de Comunicación mediante LoRa

Descripción:

En este apartado esta la  implementación de la comunicación LoRa utilizando módulos SX1278 conectados a un ESP32. Se describe cómo configurar los módulos para la transmisión y recepción de datos a largas distancias sin necesidad de infraestructura de red. El documento incluye tanto la configuración del hardware como del software, junto con pruebas para medir el alcance y la estabilidad de la comunicación.

Procedimientos Realizados:

Configuración de los módulos LoRa SX1278 para transmisión y recepción de datos.
Pruebas de alcance en campo abierto y entornos controlados.
Validación de la estabilidad de la comunicación a distintas distancias.

Conclusión:

La tecnología LoRa es excelente para aplicaciones que requieren comunicación a larga distancia con un bajo consumo de energía. Es especialmente útil en áreas remotas donde no hay acceso a redes Wi-Fi o celulares. Sin embargo, la tasa de transferencia de datos es más baja en comparación con otras tecnologías.

## Implementación de Comunicación mediante Bluetooth

Descripción:

En este apartado esta la implementación de Bluetooth utilizando el ESP32 para establecer una comunicación directa entre el microcontrolador y un dispositivo móvil. El documento detalla cómo configurar el módulo Bluetooth, cómo emparejar el dispositivo con un teléfono móvil y cómo enviar y recibir datos en tiempo real.

Procedimientos Realizados:

Configuración del Bluetooth en el ESP32 para la comunicación con un teléfono móvil.
Pruebas de transmisión y recepción de datos entre el ESP32 y el móvil.
Implementación de control remoto de un LED a través de Bluetooth desde una aplicación móvil.

Conclusión:

La comunicación Bluetooth es ideal para aplicaciones de corto alcance y control local de dispositivos. La implementación es simple y permite interacciones directas con el usuario a través de dispositivos móviles. Aunque su alcance es limitado, ofrece una solución confiable para escenarios de control a corta distancia.

## Conclusión General:

En este desarrollo de este proyecto, se ha podido establecer una comprensión profunda de las capacidades de cada tecnología de comunicación:

- Wi-Fi es ideal para aplicaciones con acceso a redes de internet y donde se requiere una alta velocidad de transmisión de datos.
- LoRa es perfecto para entornos donde se necesita comunicación de largo alcance y bajo consumo de energía, aunque con una velocidad de transmisión más baja.
- Bluetooth es adecuado para el control de dispositivos a corta distancia y ofrece una solución rápida para aplicaciones de interacción directa con el usuario.

Cada tecnología tiene su propio conjunto de ventajas y limitaciones, lo que permite elegir la más adecuada según los requisitos de la aplicación. Esta carpeta proporciona una guía práctica para implementar cualquiera de estas tecnologías en proyectos IoT, con documentación detallada de cada paso y lecciones aprendidas durante el proceso.


 ## Actualizacion
20240920
Se actualizo Readme.
