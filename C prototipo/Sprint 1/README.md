# Tecnicatura Superior en Telecomunicaciones
### Profesores: Gonzalo Vera, Jorge Morales, Dante Violi  

## Informacion General
***
### Carpeta: ***D Prototipo*** 

__La carpeta "C Prototipo" esta toda la documentación y materiales relacionados con el desarrollo y evaluación del prototipo. En esta carpeta se incluyen:__  

__Diseño y Planificación:__ Planos, esquemas, y especificaciones técnicas del prototipo, junto con la planificación del proceso de desarrollo.    

__Documentación del Desarrollo:__ Registros detallados de cada etapa del proceso de construcción, incluyendo materiales utilizados, técnicas aplicadas, y modificaciones realizadas.  

__Resultados de Pruebas:__ Informes y datos derivados de las pruebas realizadas al prototipo, incluyendo análisis de rendimiento y cualquier ajuste necesario.  

__Problemas y Soluciones:__ Descripción de problemas encontrados durante el desarrollo y las soluciones implementadas para resolverlos.  

__Referencias y Recursos:__ Cualquier recurso adicional, como manuales, guías técnicas y referencias relevantes para el desarrollo del prototipo.
***
### Avance 1: Definición de Componentes y Funcionalidades  
! Completar !!!  
***  

### Avance 2: Diseño y Planificación del Prototipo  
! Completar !!!  
***  

### Avance 3: Instalación y Pruebas Iniciales de Hardware

## Objetivos
- **Instalar sensores y actuadores seleccionados**: Configurar y conectar los componentes hardware.
- **Realizar pruebas iniciales de funcionamiento**: Verificar que los componentes funcionen correctamente.
- **Configurar dispositivos y librerías en ESP32**: Asegurar la correcta integración de hardware con el microcontrolador.
- **Documentar resultados de pruebas iniciales**: Crear reportes de las pruebas realizadas y los resultados obtenidos.

## Desarrollo: Semana 3
- **Materia Responsable**: Electrónica Microcontrolada
- **Objetivo de la Semana**: Instalar y probar los sensores y actuadores seleccionados.

### Actividades
1. **Instalación física de sensores y actuadores** (Completada)
   - Se realizó la instalación física de los sensores y actuadores en la estructura del sistema.
   - Se conectaron los componentes al microcontrolador ESP32 según el esquema de conexión.
   
![Distribucion de componentes](../../E%20recursos/Instalacion%20Fisica%20de%20Sensores%20y%20Actuadores.png)
   
2. **Conexión de los componentes al microcontrolador ESP32**
   - Conexión de sensores de humedad, DHT11, sensor de lluvia, sensor ultrasónico, LDR, micrófono electret y sensores PIR.
   - Conexión de actuadores: Tira LED WS2812B y módulo de relé de 4 canales.
   
  ![Conexiones](../../E%20recursos/Conexion%20fp_controlador_cultivo.png)

3. **Realización de pruebas iniciales de funcionamiento**
   - Verificación del correcto funcionamiento de los sensores y actuadores.
   - Configuración inicial de las librerías necesarias en el ESP32.

4. **Configuración de librerías en ESP32**
   - Integración y configuración de las librerías de los sensores y actuadores en el código del ESP32.

5. **Documentación de los resultados de las pruebas iniciales**
   - Registro detallado de los pasos de instalación y configuración.
   - Ajustes y calibraciones necesarias basadas en los resultados de las pruebas.
   - Preparación de un informe de pruebas iniciales y presentación de los resultados al equipo.

## Resultados Concretos Esperados
- Sensores y actuadores instalados y conectados al ESP32.
- Librerías configuradas en ESP32.
- Informe de pruebas iniciales documentado.
- Ajustes y calibraciones realizados.
- Presentación de resultados de pruebas al equipo.

## Historia de Usuario
"YO COMO estudiante QUIERO instalar y probar los sensores y actuadores PARA asegurar su correcto funcionamiento en el proyecto IoT."

## Sprint 1 [Product Backlog]
- Instalación física de sensores.
- Instalación física de actuadores.
- Conexión de sensores al ESP32.
- Conexión de actuadores al ESP32.
- Realización de pruebas iniciales de sensores.
- Realización de pruebas iniciales de actuadores.
- Configuración de librerías necesarias en ESP32.
- Documentación de los pasos de instalación.
- Registro de resultados de pruebas iniciales.
- Ajustes y calibraciones necesarias.
- Preparación de un informe de pruebas iniciales.
- Presentación de los resultados de pruebas al equipo.

## Esquema de Conexión de Componentes

### Entradas Analógicas y Digitales
1. **Sensores de Humedad del Suelo (HW-080) (x3):**
   - Sensor 1: GPIO36 (ADC1_CHANNEL_0)
   - Sensor 2: GPIO39 (ADC1_CHANNEL_3)
   - Sensor 3: GPIO34 (ADC1_CHANNEL_6)
2. **DHT11 (Temperatura y Humedad):**
   - GPIO14 (Digital)
3. **Sensor de Lluvia (AB119):**
   - GPIO33 (Digital)
4. **Sensor Ultrasónico (HC-SR04):**
   - Trigger: GPIO12
   - Echo: GPIO13
5. **LDR (Luz Ambiente):**
   - GPIO32 (ADC1_CHANNEL_4)
6. **Micrófono Electret:**
   - GPIO35 (ADC1_CHANNEL_7)
7. **Sensores PIR (HCSR501) (x3):**
   - Sensor 1: GPIO25
   - Sensor 2: GPIO26
   - Sensor 3: GPIO27

### Salidas
1. **Tira LED WS2812B:**
   - GPIO15 (Digital)
2. **Módulo de Relé de 4 Canales:**
   - Canal 1 (Bomba de Agua): GPIO4
   - Canal 2 (Válvula 1): GPIO16
   - Canal 3 (Válvula 2): GPIO17
   - Canal 4 (Válvula 3): GPIO0

### Interfaces de Comunicación
- **SPI:**
  - MOSI: GPIO23
  - MISO: GPIO19
  - SCK: GPIO18
  - SS (NSS): GPIO5
- **I2C:**
  - SCL: GPIO22
  - SDA: GPIO21

## Resumen Completo
- **Entradas Analógicas:**
  - GPIO36, GPIO39, GPIO34, GPIO32, GPIO35
- **Entradas Digitales:**
  - GPIO14, GPIO33, GPIO12, GPIO13, GPIO25, GPIO26, GPIO27
- **Salidas Digitales:**
  - GPIO15 (tira LED), GPIO4 (Relé Canal 1), GPIO16 (Relé Canal 2), GPIO17 (Relé Canal 3), GPIO0 (Relé Canal 4)
- **SPI:**
  - MOSI: GPIO23
  - MISO: GPIO19
  - SCK: GPIO18
  - SS: GPIO5
- **I2C:**
  - SCL: GPIO22
  - SDA: GPIO21
