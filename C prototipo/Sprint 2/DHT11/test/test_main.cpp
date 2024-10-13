#include <Arduino.h>
#include <unity.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Variables globales para los resultados
float humidity;
float temperature;

// Configuración inicial del sensor
void setup() {
    delay(2000);
    UNITY_BEGIN();
    dht.begin();
}

// Test para verificar la lectura de humedad
void test_humidity_read() {
    humidity = dht.readHumidity();
    TEST_ASSERT_FALSE(isnan(humidity)); // Comprobar que no sea NaN
    TEST_ASSERT_TRUE(humidity >= 20 && humidity <= 100);
}

// Test para verificar la lectura de temperatura
void test_temperature_read() {
    temperature = dht.readTemperature();
    TEST_ASSERT_FALSE(isnan(temperature)); // Comprobar que no sea NaN
    TEST_ASSERT_TRUE(temperature >= 0 && temperature <= 50);
}

// Ejecuta los tests
void loop() {
    RUN_TEST(test_humidity_read);
    RUN_TEST(test_temperature_read);
    UNITY_END();
    delay(5000);  // Ejecuta los tests cada 5 segundos
}
