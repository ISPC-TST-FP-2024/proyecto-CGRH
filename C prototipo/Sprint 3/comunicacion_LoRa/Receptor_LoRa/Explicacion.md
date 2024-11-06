# Comunicación entre ESP32 usando LoRa SX1278
## 1. Introducción
En este proyecto se busca implementar una comunicación punto a punto entre dos ESP32 NodeMCU-32S utilizando módulos LoRa RA-01 (SX1278). El sistema consistirá en un emisor que enviará datos y un receptor que los mostrará en una pantalla LCD 2x20, con la confirmación de recepción mediante un ACK. A continuacion se detalla el diseño completo, asignación de pines y la estructura del código para facilitar su implementación.

## 2. Materiales Necesarios
- 2x ESP32 NodeMCU-32S
- 2x Módulo LoRa RA-01 (SX1278)
- 1x Pantalla LCD 2x20 con adaptador I2C
- 1x Botón pulsador
- 1x LED
- Cables jumper macho-macho y macho-hembra
- Protoboard  

## 3. Diagrama de conexión
### 3.1. Conexión del Módulo LoRa RA-01 al ESP32 NodeMCU-32S
|Módulo LoRa RA-01 (SX1278)|ESP32 NodeMCU-32S|  
|:-------|:------|
|VCC |3V3|  
|GND |GND|  
|MISO |GPIO 19|
|MOSI|GPIO 23| 
|SCK|GPIO 18|
|NSS (CS)|GPIO 5|
|RESET|GPIO 14|
|DIO0|GPIO 2|

### 3.2. Conexión del botón y el LED (Emisor)
* Botón: Conectar un extremo al GPIO 12 y el otro a GND (con resistencia pull-up interna activada).  

* LED: Conectar el ánodo al GPIO 13 y el cátodo a GND.  

### 3.3. Conexión del LCD 2x20 (Receptor)
* SDA del LCD al GPIO 21 (I2C SDA)  

* SCL del LCD al GPIO 22 (I2C SCL)  

## 4. Instalación del Entorno
PlatformIO en Vscode

* Generar un nuevo proyecto de PlatformIO para la placa nodeMCU-32S
* Elegir el directorio adecuado   
* Instalar las siguientes librerías desde el gestor de librerías:
    - LoRa de Sandeep Mistry.
    - LiquidCrystal_I2C de marcoschwartz para el LCD con I2C.  

## 5. Flujo del Código  

### Emisor  

* Cuando el botón se presiona, se genera un mensaje aleatorio y se envía a través del módulo LoRa.
* Si el emisor recibe un mensaje ACK del receptor, enciende un LED durante un segundo.  

### Receptor
* Escucha constantemente los mensajes entrantes mediante el módulo LoRa.
* Al recibir un mensaje, lo muestra en la pantalla LCD.
* Envía un mensaje ACK de vuelta al emisor.

# Es posible mejorar el algoritmo para que los controladores no esten leyendo el botón o escuchando los mensajes constántemente?  
Es posible mediante el uso de las interrupciones. 
Una interrupción, como su nombre lo indica, corta el flujo normal del programa para atender una actividad determinada y luego devuelve el control del flujo a donde había quedado.   

## ISR en Microcontroladores: Reglas y Buenas Prácticas
* ISR deben ser cortas y rápidas:
  * Las interrupciones bloquean otras operaciones críticas del sistema. Ejecutar procesos largos (como comunicación SPI con LoRa) puede llevar a problemas de latencia o pérdida de interrupciones.  

* No se recomienda llamar a funciones complejas en la ISR:
  * Comunicaciones por SPI (como con el módulo LoRa) pueden ser problemáticas desde una ISR, ya que SPI usa interrupciones y podría generar un conflicto.
  * Manipular objetos de clase o funciones complejas podría llevar a comportamientos inesperados.  

* Alternativa recomendada:
  * Usar una bandera en la ISR y delegar el procesamiento al loop() es más seguro.  

Asi, podemos mejorar la eficiencia del codigo y optimizar el manejo de eventos sin bloquear la ISR.  

## Implementación con Debounce Directo en la ISR
Podemos hacer debounce en la ISR del botón y disparar directamente el método de envío o recepción en loop(), siguiendo las buenas prácticas.

### Código Mejorado para el Emisor con Debounce en ISR

Se implementa un debounce en la ISR para evitar múltiples interrupciones y llamamos el envío desde el loop() con mínima latencia.

```cpp
#include <Arduino.h>
#include "com_LoRa.h"
#include "lcdDisplay.h"

com_LoRa lora(433E6);
lcdDisplay display;

volatile bool mensajeDisponible = false;

void IRAM_ATTR isrLoRa() {
    mensajeDisponible = true;  // Bandera para recibir mensaje
}

void setup() {
    Serial.begin(9600);
    display.init();
    lora.init();

    // Configura interrupción en DIO0
    attachInterrupt(digitalPinToInterrupt(2), isrLoRa, RISING);

    Serial.println("Receptor listo.");
}

void loop() {
    if (mensajeDisponible) {
        mensajeDisponible = false;  // Reinicia bandera

        // Procesa el mensaje recibido
        String mensaje = lora.receiveMessage();
        if (mensaje != "") {
            Serial.println("Mensaje recibido: " + mensaje);
            display.showMessage(mensaje);  // Mostrar en LCD

            lora.sendMessage("ACK");
            Serial.println("ACK enviado.");
        }
    }
}

```   

## Llamadas a funciones dentro de la ISR vs Uso de Banderas en loop()
**1- Interrupciones son para eventos rápidos:** Las ISR deben ser cortas, manejando solo lógica simple como debounce o actualización de banderas.  

**2- Uso seguro de SPI y LoRa:** Como SPI depende de interrupciones internas, el procesamiento complejo debe hacerse en el loop() para evitar conflictos.  

**3- Mínima latencia:** Esta implementación ofrece una respuesta casi inmediata sin bloquear el sistema ni arriesgar conflictos.


