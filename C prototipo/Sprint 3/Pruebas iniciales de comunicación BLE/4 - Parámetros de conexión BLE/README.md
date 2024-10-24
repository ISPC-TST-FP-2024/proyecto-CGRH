# Proyecto ESP32: Ajuste de Parámetros de Conexión BLE

Este proyecto implementa una funcionalidad de Bluetooth Low Energy (BLE) en un ESP32, enfocándose en la estabilidad de la conexión, el ajuste de parámetros de publicidad, y la reconexión automática cuando un dispositivo se desconecta.

## Funcionamiento

El código permite al ESP32 actuar como un servidor BLE que ofrece un servicio y una característica para la comunicación con clientes BLE. Cuando un cliente BLE se conecta al ESP32, se pueden enviar notificaciones. Además, el proyecto incluye mecanismos para ajustar los parámetros de conexión y publicidad BLE, así como gestionar la reconexión automática cuando un dispositivo cliente se desconecta.

### Principales Funciones

1. **Inicialización BLE**: Configura el servidor BLE, crea un servicio y una característica, y comienza la publicidad para que los dispositivos puedan descubrir el ESP32.
2. **Notificación a Clientes**: Si un dispositivo está conectado, el ESP32 puede enviar notificaciones periódicas con datos al cliente.
3. **Ajuste de Parámetros**: Se permite modificar los intervalos de publicidad BLE y los parámetros de conexión para optimizar el rendimiento según las pruebas.
4. **Reconexion Automática**: Cuando un dispositivo se desconecta, el ESP32 automáticamente vuelve a emitir su señal de publicidad para permitir la reconexión.

## Archivos del Proyecto

- `ble_ajuste_parametros.h`: Contiene la declaración de la clase que gestiona el BLE y los parámetros de conexión.
- `ble_ajuste_parametros.cpp`: Implementa las funciones principales para la inicialización del BLE, ajuste de parámetros y manejo de la reconexión.
- `main.cpp`: Punto de entrada del programa, inicializa el BLE y realiza las notificaciones periódicas.

## Cómo Probar el Proyecto

### Requisitos

- **ESP32**: Este código está diseñado para ser ejecutado en un ESP32.
- **Aplicación BLE en un Dispositivo**: Puedes utilizar una aplicación BLE como **nRF Connect** o **LightBlue** para conectarte al ESP32.
- **PlatformIO**: El proyecto está configurado para PlatformIO. Asegúrate de tenerlo instalado para compilar y cargar el código.

### Instrucciones

1. **Compila y sube el código al ESP32** usando PlatformIO.
2. **Abre el monitor serie** para ver los mensajes de estado e información sobre la conexión BLE.
3. **Conéctate al ESP32** desde una aplicación BLE (nRF Connect, LightBlue, etc.).
4. **Envía notificaciones BLE**: Una vez conectado, el ESP32 enviará mensajes periódicos al dispositivo cliente.
5. **Prueba la desconexión**: Desconecta el dispositivo y verifica en el monitor serie que el ESP32 comienza a esperar reconexiones.
6. **Reconéctate** al ESP32 y verifica que se realiza la reconexión automáticamente.

## Ajuste de Parámetros

Puedes ajustar los siguientes parámetros en el código:

- **Intervalo de publicidad**: El intervalo en milisegundos en el que el ESP32 emite su señal de publicidad para ser descubierto por dispositivos BLE.
- **Parámetros de conexión**: Se pueden modificar los intervalos de conexión y el tiempo de espera de la conexión para mejorar la estabilidad o el consumo energético.
