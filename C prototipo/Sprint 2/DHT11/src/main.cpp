#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Definir el pin del sensor DHT11
#define DHTPIN 4     // Cambia este pin según tu conexión
#define DHTTYPE DHT11   // Cambia a DHT22 si usas ese sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();
    Serial.println("Inicializando sensor DHT11...");
}

void loop() {
    delay(2000); // El DHT11 se lee aproximadamente cada 2 segundos

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    // Verificar si las lecturas son válidas
    if (isnan(h) || isnan(t)) {
        Serial.println("Error al leer el sensor DHT11");
        return;
    }

    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
}
