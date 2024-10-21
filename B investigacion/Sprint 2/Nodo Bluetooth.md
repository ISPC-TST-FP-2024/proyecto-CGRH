# Sistema de Riego Inteligente con Nodo Bluetooth

Este documento describe el funcionamiento energético del nodo Bluetooth para un sistema de riego vertical, diseñado para invernaderos o instalaciones cerradas. Incluye los cálculos de consumo de energía, opciones de alimentación y la integración de un LED de espectro completo para el crecimiento de las plantas.

## Componentes del Nodo Bluetooth

1. **Microcontrolador ESP32 (Bluetooth Integrado)**:
   - **Función**: Procesa los datos de los sensores y transmite vía Bluetooth al nodo central.
   - **Consumo de energía**:
     - Modo activo (Bluetooth conectado): **160 mA**.
     - Modo suspensión profunda: **10 µA**.

2. **Sensor de Humedad del Suelo Capacitivo (YL-69)**:
   - **Función**: Mide la humedad del suelo.
   - **Consumo**: **15 mA**.

3. **Sensor de Temperatura y Humedad (DHT22)**:
   - **Función**: Mide la temperatura y la humedad del aire.
   - **Consumo**: **2.5 mA**.

4. **Sensor de Luz (BH1750)**:
   - **Función**: Mide la cantidad de luz recibida por las plantas.
   - **Consumo**: **0.12 mA**.

5. **Pantalla OLED (0.96")**:
   - **Función**: Muestra los valores actuales de los sensores y el estado del sistema.
   - **Consumo**: **20 mA**.

6. **Bomba de Agua**:
   - **Función**: Distribuye agua en el sistema de riego vertical.
   - **Consumo**: **200 mA - 1A** (en uso).

7. **LED de Espectro Completo**:
   - **Función**: Ilumina a las plantas con luz adecuada para su crecimiento.
   - **Consumo**: **200 mA - 500 mA** dependiendo de la intensidad.

## Consumo Total del Sistema

### 1. Sin la bomba y el LED:
Suma de los consumos:

160 mA (ESP32) + 15 mA (sensor de humedad) + 2.5 mA (DHT22) + 0.12 mA (sensor de luz) + 20 mA (OLED) = 197.62 mA

### 2. Con la bomba y el LED activos:
Sumamos el consumo de la bomba y el LED:

197.62 mA + 200 mA (bomba) + 200 mA (LED) = 597.62 mA


Con la bomba y el LED encendidos, el consumo sube a aproximadamente **600 mA**.

## Opciones de Alimentación

### 1. Alimentación con Batería LiPo + Panel Solar

Podés usar una batería **LiPo de 1000 mAh o 3000 mAh** y un panel solar para recargarla.

#### Cálculo del panel solar:
Si queremos que la batería se recargue en 6 horas de luz solar directa, el panel debe generar suficiente corriente.

Para una batería de **1000 mAh**:

Corriente del panel = 1000 mAh / 6 h = 166.67 mA


Para una batería de **3000 mAh**:

Corriente del panel = 3000 mAh / 6 h = 500 mA


Esto significa que necesitás:
- Un **panel solar de 5V 1W** para una batería de 1000 mAh.
- Un **panel solar de 5V 2.5W** o más para una batería de 3000 mAh.

Además, se necesita un **módulo TP4056** para gestionar la carga de la batería.

### 2. Alimentación con Recarga USB

Si preferís no usar panel solar, podés recargar la batería manualmente por **USB**.

Un cargador USB de **5V 1A** recarga una batería de **1000 mAh** en aproximadamente 1 hora, y una de **3000 mAh** en unas 3 horas.

### 3. Alimentación Continua (Panel Solar o USB)

Para alimentar el sistema de manera continua, sin depender de la batería, podés utilizar:
- Un **panel solar de 5V 3W** para asegurar suficiente energía.
- Una **fuente USB de 5V 2A** para alimentación directa.

### 4. Alimentación por Corriente Alterna (CA)

También se puede conectar el sistema a la corriente utilizando un **adaptador de 220V a 5V**. Un ejemplo sería una **fuente de 5V 2A**, que convierte los **220V de CA** en **5V de CC** para alimentar el nodo de manera estable.

## Opciones de Alimentación del Sistema

1. **Batería LiPo + Panel Solar**:
   - Para una batería de **1000 mAh**: Panel solar de **5V 1W**.
   - Para una batería de **3000 mAh**: Panel solar de **5V 2.5W** o más.

2. **Recarga USB Manual**:
   - Cargador de **5V 1A o 2A** es suficiente para recargar las baterías.

3. **Alimentación Continua**:
   - **Panel solar de 5V 3W** o **fuente USB de 5V 2A** para alimentación continua.

4. **Alimentación por Corriente Alterna (CA)**:
   - Adaptador **220V a 5V 2A** para conexión directa a la red eléctrica.

---

Este informe detalla las opciones energéticas y componentes necesarios para construir un sistema de riego eficiente, adaptable a diferentes formas de alimentación, ya sea solar, USB o directamente desde la red eléctrica. ¡Elegí la opción que más te convenga y asegurate de tener siempre tu sistema funcionando!
