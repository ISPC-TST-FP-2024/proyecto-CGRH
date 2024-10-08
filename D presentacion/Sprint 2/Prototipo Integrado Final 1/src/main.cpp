// ----------------------------------------------------------------
// Prototipo:
// En proceso, evaluando la estructura general medinte el uso de FreeRTOS.
// Asi mismo estamos reevaluando cada bloque de codigo de cada sensor, 
// para compatibilizar, y sea choerente con la funcion FreeRTOS propuesta
// ----------------------------------------------------------------


#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>

// Incluye librerías de los módulos de conectividad
#include "conexiones/wifi.h"
#include "conexiones/lora.h"
#include "conexiones/ble.h"

// Incluye librerías de los sensores
#include "sensores/sensor_aht10.h"
#include "sensores/sensor_bh1750.h"
#include "sensores/sensor_dht11.h"
#include "sensores/sensor_ldr.h"
#include "sensores/sensor_hcsr04.h"
#include "sensores/sensor_humedad_suelo.h"

// Tarea para el Sensor de Humedad del Suelo
void TareaSensorHumedadSuelo(void *pvParameters) {
    while(1) {
        int humedad = leerHumedadSuelo();
        if(humedad < THRESHOLD_HUMEDAD) {
            activarBomba();
        } else {
            desactivarBomba();
        }
        vTaskDelay(pdMS_TO_TICKS(5000)); // Leer cada 5 segundos
    }
}

// Tarea para el Sensor de Nivel de Agua (HC-SR04)
void TareaSensorNivelAgua(void *pvParameters) {
    while(1) {
        int nivelAgua = leerNivelAgua();
        if(nivelAgua < THRESHOLD_NIVEL_AGUA) {
            detenerBomba();
        }
        vTaskDelay(pdMS_TO_TICKS(10000)); // Leer cada 10 segundos
    }
}

// Tarea para el Sensor de Temperatura y Humedad Ambiental (AHT10 o DHT11)
void TareaSensorTemperaturaHumedad(void *pvParameters) {
    while(1) {
        float temperatura = leerTemperatura();
        float humedad = leerHumedad();
        // Registrar o utilizar valores según sea necesario
        vTaskDelay(pdMS_TO_TICKS(15000)); // Leer cada 15 segundos
    }
}

// Tarea para el Sensor de Luz (LDR)
void TareaSensorLuzLDR(void *pvParameters) {
    while(1) {
        int luz = leerLuzLDR();
        // Procesar datos de luz
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para el Sensor de Luz (BH1750)
void TareaSensorLuzBH1750(void *pvParameters) {
    while(1) {
        int luzBH1750 = leerLuzBH1750();
        // Procesar datos de luz precisa
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para la Conexión WiFi
void TareaWiFi(void *pvParameters) {
    while(1) {
        enviarDatosWiFi();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

// Tarea para la Conexión LoRa
void TareaLoRa(void *pvParameters) {
    while(1) {
        enviarDatosLoRa();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

// Tarea para la Conexión Bluetooth
void TareaBLE(void *pvParameters) {
    while(1) {
        enviarDatosBLE();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

void setup() {
    // Inicialización de sensores y conexiones
    inicializarWiFi();
    inicializarLoRa();
    inicializarBLE();
    inicializarSensorHumedadSuelo();
    inicializarSensorNivelAgua();
    inicializarSensorAHT10();
    inicializarSensorBH1750();
    inicializarSensorLDR();
    inicializarSensorDHT11();

    // Crear tareas
    xTaskCreate(TareaSensorHumedadSuelo, "Humedad Suelo", 128, NULL, 3, NULL);
    xTaskCreate(TareaSensorNivelAgua, "Nivel Agua", 128, NULL, 3, NULL);
    xTaskCreate(TareaSensorTemperaturaHumedad, "Temp Humedad", 128, NULL, 2, NULL);
    xTaskCreate(TareaSensorLuzLDR, "Luz LDR", 128, NULL, 1, NULL);
    xTaskCreate(TareaSensorLuzBH1750, "Luz BH1750", 128, NULL, 1, NULL);
    xTaskCreate(TareaWiFi, "WiFi", 128, NULL, 2, NULL);
    xTaskCreate(TareaLoRa, "LoRa", 128, NULL, 2, NULL);
    xTaskCreate(TareaBLE, "BLE", 128, NULL, 2, NULL);

    // Iniciar el scheduler de FreeRTOS
    vTaskStartScheduler();
}

void loop() {
    // FreeRTOS gestiona las tareas, no se utiliza loop() aquí
}
