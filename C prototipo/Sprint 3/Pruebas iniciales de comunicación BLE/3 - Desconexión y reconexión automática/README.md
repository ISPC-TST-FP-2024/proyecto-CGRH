# Práctica BLE en ESP32: Reconexión y Notificación de Clientes

## Descripción

Este programa implementa una funcionalidad BLE (Bluetooth Low Energy) en el ESP32 que permite:

- Crear un servidor BLE que se puede conectar con dispositivos externos.
- Detectar y gestionar la conexión y desconexión de dispositivos BLE.
- Notificar datos a los clientes conectados.
- Reiniciar la publicidad BLE automáticamente cuando un dispositivo se desconecta, permitiendo la reconexión.

## Componentes Principales

1. **`BLE_Reconnect` (ble_reconnect.h y ble_reconnect.cpp)**:
   - **Clase BLE_Reconnect**: Gestiona el servidor BLE y las conexiones de dispositivos.
   - **Funciones**:
     - `initBLE()`: Inicializa el módulo BLE, crea el servidor y la característica para la notificación.
     - `notifyClients()`: Envía datos a los dispositivos conectados.
     - `checkConnection()`: Verifica el estado de la conexión, reinicia la publicidad si el dispositivo se desconecta.
     - Getters y setters para manejar el estado de conexión (`deviceConnected`, `oldDeviceConnected`).

2. **Callbacks de BLE**:
   - **MyServerCallbacks**: Se utiliza para capturar los eventos de conexión y desconexión de dispositivos. Actualiza el estado de conexión del servidor y muestra mensajes en el monitor serie.

3. **`main.cpp`**:
   - En el `setup()`, se inicializa el BLE.
   - En el `loop()`, se verifica constantemente el estado de la conexión y se envían notificaciones a los clientes si están conectados.

## Funcionamiento

- El ESP32 actúa como servidor BLE y espera a que un dispositivo cliente (como un smartphone) se conecte.
- Cuando el dispositivo se conecta, el servidor actualiza su estado y comienza a enviar notificaciones.
- Si el cliente se desconecta, el ESP32 reinicia la publicidad para que el cliente pueda reconectarse automáticamente.
- Las notificaciones incluyen un mensaje enviado desde el ESP32 a los clientes conectados.

## Cómo Probarlo

1. **Configurar el ESP32**:
   - Sube el código al ESP32 utilizando PlatformIO.
   - Abre el monitor serie para visualizar el estado de la conexión.

2. **Conectar un Cliente BLE**:
   - Usa una app de escaneo BLE en tu smartphone, como **nRF Connect** o **LightBlue**.
   - Busca el dispositivo con el nombre "ESP32 BLE Reconnect" y conéctate a él.

3. **Ver Notificaciones**:
   - Al conectarte, verás en la consola del ESP32 mensajes indicando que el dispositivo está conectado.
   - El ESP32 enviará notificaciones a través del canal BLE creado, las cuales pueden ser visualizadas en la app BLE del smartphone.

4. **Simular Desconexión**:
   - Desconecta el cliente BLE desde la app.
   - El ESP32 comenzará a buscar nuevamente dispositivos para reconectar. Al reconectarte, verás el mensaje "Reconexión exitosa" en el monitor serie.


