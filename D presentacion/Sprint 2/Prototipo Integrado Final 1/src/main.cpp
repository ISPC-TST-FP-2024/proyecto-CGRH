// ----------------------------------------------------------------
// Prototipo:
// En proceso, evaluando la estructura general medinte el uso de FreeRTOS.
// Asi mismo estamos reevaluando cada bloque de codigo de cada sensor, 
// para compatibilizar, y sea choerente con la funcion FreeRTOS propuesta
// ----------------------------------------------------------------

#include <Arduino.h>
#include <FreeRTOS.h>
#include <task.h>
#include <nvs_flash.h>
#include <nvs.h>

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

// Almacenamiento en NVS
nvs_handle_t nvsHandle;
bool wifiHabilitado = true;
bool bleHabilitado = true;
bool loraHabilitado = true;

// Función para guardar configuraciones en la memoria no volátil (NVS)
void guardarConfiguracion(const char* key, int valor) {
    nvs_open("configuracion", NVS_READWRITE, &nvsHandle);
    nvs_set_i32(nvsHandle, key, valor);
    nvs_commit(nvsHandle);
    nvs_close(nvsHandle);
}

// Función para leer configuraciones de la memoria no volátil (NVS)
int leerConfiguracion(const char* key, int valorDefecto) {
    nvs_open("configuracion", NVS_READWRITE, &nvsHandle);
    int valor;
    if (nvs_get_i32(nvsHandle, key, &valor) != ESP_OK) {
        valor = valorDefecto;
        nvs_set_i32(nvsHandle, key, valor);
        nvs_commit(nvsHandle);
    }
    nvs_close(nvsHandle);
    return valor;
}

// Tarea para el Sensor de Humedad del Suelo
void TareaSensorHumedadSuelo(void *pvParameters) {
    while (1) {
        int humedad = leerHumedadSuelo();
        if (humedad < THRESHOLD_HUMEDAD) {
            activarBomba();
        } else {
            desactivarBomba();
        }
        vTaskDelay(pdMS_TO_TICKS(5000)); // Leer cada 5 segundos
    }
}

// Tarea para el Sensor de Nivel de Agua (HC-SR04)
void TareaSensorNivelAgua(void *pvParameters) {
    while (1) {
        int nivelAgua = leerNivelAgua();
        if (nivelAgua < THRESHOLD_NIVEL_AGUA) {
            detenerBomba();
        }
        vTaskDelay(pdMS_TO_TICKS(10000)); // Leer cada 10 segundos
    }
}

// Tarea para el Sensor de Temperatura y Humedad Ambiental (AHT10 o DHT11)
void TareaSensorTemperaturaHumedad(void *pvParameters) {
    while (1) {
        float temperatura = leerTemperatura();
        float humedad = leerHumedad();
        // Registrar o utilizar valores según sea necesario
        vTaskDelay(pdMS_TO_TICKS(15000)); // Leer cada 15 segundos
    }
}

// Tarea para el Sensor de Luz (LDR)
void TareaSensorLuzLDR(void *pvParameters) {
    while (1) {
        int luz = leerLuzLDR();
        // Procesar datos de luz
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para el Sensor de Luz (BH1750)
void TareaSensorLuzBH1750(void *pvParameters) {
    while (1) {
        int luzBH1750 = leerLuzBH1750();
        // Procesar datos de luz precisa
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para la Conexión WiFi
void TareaWiFi(void *pvParameters) {
    while (wifiHabilitado) {
        enviarDatosWiFi();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

// Tarea para la Conexión LoRa
void TareaLoRa(void *pvParameters) {
    while (loraHabilitado) {
        enviarDatosLoRa();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

// Tarea para la Conexión Bluetooth
void TareaBLE(void *pvParameters) {
    while (bleHabilitado) {
        enviarDatosBLE();
        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

// Tarea para el Menú
void TareaMenu(void *pvParameters) {
    while (1) {
        Serial.println("Menú principal:");
        Serial.println("1. Mostrar estado de WiFi");
        Serial.println("2. Conectar a WiFi");
        Serial.println("3. Iniciar Bluetooth");
        Serial.println("4. Habilitar/Deshabilitar WiFi");
        Serial.println("5. Habilitar/Deshabilitar LoRa");
        Serial.println("6. Habilitar/Deshabilitar BLE");
        Serial.println("7. Guardar configuración y salir");

        if (Serial.available()) {
            char opcion = Serial.read();
            switch (opcion) {
                case '1':
                    estadoWiFi();
                    break;
                case '2':
                    conectarWiFi();
                    break;
                case '3':
                    iniciarBle();
                    break;
                case '4':
                    wifiHabilitado = !wifiHabilitado;
                    Serial.println(wifiHabilitado ? "WiFi habilitado" : "WiFi deshabilitado");
                    break;
                case '5':
                    loraHabilitado = !loraHabilitado;
                    Serial.println(loraHabilitado ? "LoRa habilitado" : "LoRa deshabilitado");
                    break;
                case '6':
                    bleHabilitado = !bleHabilitado;
                    Serial.println(bleHabilitado ? "BLE habilitado" : "BLE deshabilitado");
                    break;
                case '7':
                    guardarConfiguracion("wifiHabilitado", wifiHabilitado);
                    guardarConfiguracion("loraHabilitado", loraHabilitado);
                    guardarConfiguracion("bleHabilitado", bleHabilitado);
                    Serial.println("Configuración guardada.");
                    break;
                default:
                    Serial.println("Opción inválida");
                    break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Pequeña espera para no sobrecargar la CPU
    }
}

void setup() {
    Serial.begin(115200);

    // Inicialización de NVS para guardar configuraciones
    nvs_flash_init();

    // Leer configuraciones desde la memoria NVS
    wifiHabilitado = leerConfiguracion("wifiHabilitado", 1);
    loraHabilitado = leerConfiguracion("loraHabilitado", 1);
    bleHabilitado = leerConfiguracion("bleHabilitado", 1);

    // Inicialización de sensores y conexiones según configuración dinámica
    if (wifiHabilitado) inicializarWiFi();
    if (loraHabilitado) inicializarLoRa();
    if (bleHabilitado) inicializarBLE();

    inicializarSensorHumedadSuelo();
    inicializarSensorNivelAgua();
    inicializarSensorAHT10();
    inicializarSensorBH1750();
    inicializarSensorLDR();
    inicializarSensorDHT11();

    // Crear tareas
    xTaskCreate(TareaSensorHumedadSuelo, "Humedad Suelo", 256, NULL, 3, NULL);
    xTaskCreate(TareaSensorNivelAgua, "Nivel Agua", 256, NULL, 3, NULL);
    xTaskCreate(TareaSensorTemperaturaHumedad, "Temp Humedad", 256, NULL, 2, NULL);
    xTaskCreate(TareaSensorLuzLDR, "Luz LDR", 128, NULL, 1, NULL);
    xTaskCreate(TareaSensorLuzBH1750, "Luz BH1750", 128, NULL, 1, NULL);

    // Crear tareas de conexión según configuración
    if (wifiHabilitado) xTaskCreate(TareaWiFi, "WiFi", 512, NULL, 2, NULL);
    if (loraHabilitado) xTaskCreate(TareaLoRa, "LoRa", 512, NULL, 2, NULL);
    if (bleHabilitado) xTaskCreate(TareaBLE, "BLE", 512, NULL, 2, NULL);

    // Crear tarea para el menú interactivo
    xTaskCreate(TareaMenu, "Menu", 512, NULL, 1, NULL);

    // Iniciar el scheduler de FreeRTOS
    vTaskStartScheduler();
}

void loop() {
    // FreeRTOS gestiona las tareas, no se utiliza loop() aquí
}
