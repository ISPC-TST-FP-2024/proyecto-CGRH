
#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include <Adafruit_AHTX0.h>

// Datos de conexión WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Servidor MQTT
const char* mqtt_server = "broker.hivemq.com";

// Creación de instancias para WiFi y MQTT
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_AHTX0 sensorAHTX0; // Crea una instancia del sensor AHTX0

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

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido en el tema: ");
    Serial.println(topic);
    Serial.print("Mensaje: ");
    
    String message;
    for (int i = 0; i < length; i++) {
        message += (char)payload[i];
    }
    Serial.println(message);
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    sensorAHTX0.begin(); // Inicializar el sensor AHTX0
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }

    // Leer datos del sensor AHTX0
    sensors_event_t humidity, temp;
    sensorAHTX0.getEvent(&humidity, &temp);

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

    delay(2000);
    client.loop();
}
