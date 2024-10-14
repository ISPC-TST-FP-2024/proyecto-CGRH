#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>

// Datos de conexión WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Servidor MQTT
const char* mqtt_server = "broker.hivemq.com";

// Creación de instancias para WiFi y MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Instancia para el sensor AHT
Adafruit_AHTX0 aht;

// Función para conectar a la red WiFi
void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi conectado");
    Serial.print("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

// Función para reconectar al servidor MQTT
void reconnect() {
    while (!client.connected()) {
        Serial.print("Intentando conexión MQTT...");
        if (client.connect("ESP32Client")) {
            Serial.println("Conectado");
            client.subscribe("seguridad/tempe");
        } else {
            Serial.print("Falló, rc=");
            Serial.print(client.state());
            Serial.println(" Intentando de nuevo en 5 segundos");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi(); // Conectar a la WiFi
    client.setServer(mqtt_server, 1883); // Configurar el servidor MQTT

    // Inicializar el sensor AHTX0
    if (!aht.begin()) {
        Serial.println("No se pudo encontrar el sensor AHT!");
        while (1) delay(10);
    }
    Serial.println("Sensor AHTX0 inicializado.");
}

void loop() {
    if (!client.connected()) {
        reconnect(); // Reconnectar si es necesario
    }

    // Leer datos del sensor AHTX0
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);  // Obtiene los eventos de humedad y temperatura

    // Convertir datos a string para enviarlos por MQTT
    String temp_str = "Temp: " + String(temp.temperature, 2) + " °C";
    String humidity_str = "Humedad: " + String(humidity.relative_humidity, 2) + " %";

    // Publicar datos en el tema "seguridad/tempe"
    client.publish("seguridad/tempe", temp_str.c_str());
    client.publish("seguridad/humidity", humidity_str.c_str());

    // Imprimir datos en el monitor serial
    Serial.println(temp_str);
    Serial.println(humidity_str);
    Serial.println("---");

    delay(2000); // Esperar 2 segundos antes de la siguiente lectura
    client.loop(); // Mantener la conexión MQTT
}
