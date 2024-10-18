# Nodo LoRa para Sistema de Riego Inteligente

Este nodo es ideal para esos sistemas de riego en grandes instalaciones o exteriores, donde los nodos están más lejos del nodo central y necesitamos comunicación a larga distancia. La tecnología **LoRa** es perfecta para enviar datos a distancias de hasta **10 km en áreas rurales**. ¡Ideal para granjas o grandes superficies!

## Componentes Principales del Nodo LoRa

### 1. Microcontrolador ESP32 + Módulo LoRa (SX1276)
- **Función**: El ESP32 procesa los datos de los sensores y los manda vía **LoRa**, que permite la comunicación a larga distancia.
- **Consumo de energía**:
  - **ESP32**: **160 mA** (en operación).
  - **Módulo LoRa (SX1276)**: **50 - 130 mA** (dependiendo de si está en transmisión o recepción).

### 2. Sensores

#### a. Sensor de Humedad del Suelo (Capacitivo YL-69)
- **Función**: Mide la humedad del suelo para decidir cuándo activar el sistema de riego.
- **Consumo**: **15 mA**.

#### b. Sensor de Temperatura y Humedad (DHT22)
- **Función**: Mide la temperatura y la humedad del aire.
- **Consumo**: **2.5 mA**.

#### c. Sensor de Luz (BH1750)
- **Función**: Mide la cantidad de luz que reciben las plantas.
- **Consumo**: **0.12 mA**.

### 3. Pantalla OLED (0.96")
- **Función**: Muestra los valores de los sensores y el estado general del sistema.
- **Consumo**: **20 mA**.

### 4. Bomba de Agua
- **Función**: Sirve para regar las plantas en base a los datos de humedad.
- **Consumo**: **200 mA - 1A** (depende del modelo de la bomba).

## Consumo Total Estimado del Nodo LoRa

Para tener una idea clara, vamos a sumar todo:

1. **ESP32** en modo activo (LoRa + sensores): **240 mA** (160 mA del ESP32 + 80 mA del LoRa).
2. **Sensor de Humedad del Suelo**: **15 mA**.
3. **Sensor de Temperatura y Humedad (DHT22)**: **2.5 mA**.
4. **Sensor de Luz (BH1750)**: **0.12 mA**.
5. **Pantalla OLED**: **20 mA**.
6. **Bomba de Agua** (en uso): entre **200 mA y 1A**.

### Consumo Total sin la Bomba:

240 mA (ESP32+LoRa) + 15 mA (Humedad) + 2.5 mA (Temp) + 0.12 mA (Luz) + 20 mA (OLED) = 277.62 mA


### Consumo Total con la Bomba (200 mA):

277.62 mA + 200 mA = 477.62 mA


## Aplicación del Nodo LoRa

Este nodo LoRa está genial para esos **sistemas de riego en exteriores o áreas amplias** donde los sensores están más alejados del nodo central. La tecnología LoRa permite que los datos viajen por varios kilómetros hasta llegar a un solo punto central, ¡perfecto para monitorear grandes superficies sin Wi-Fi! Esto lo hace ideal para granjas, campos de cultivo o cualquier lugar donde los cables o el Wi-Fi no lleguen fácilmente.

## Fuente de Alimentación Recomendada

### 1. Batería LiPo de 3.7V 3000 mAh - 5000 mAh
Dado que el nodo con LoRa consume más energía que uno con Bluetooth, necesitas una **batería de mayor capacidad**. Aquí un cálculo básico:

Si el nodo consume unos **477.62 mA** en promedio (incluyendo la bomba), una batería de **3000 mAh** te duraría aproximadamente:

3000 mAh / 477.62 mA = 6.28 horas


Si necesitamos más duración, podriamos optar por una batería más grande, de **5000 mAh**, que nos duraria más de 10 horas.

### 2. Panel Solar (6V 1W) + Batería Recargable
En exteriores, un panel solar nos ayuda  el panel de **6V 1W** podra recargar una batería de respaldo para que el sistema siga funcionando toda la noche.

