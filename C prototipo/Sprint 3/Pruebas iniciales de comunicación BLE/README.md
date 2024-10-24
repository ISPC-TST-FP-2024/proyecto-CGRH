# Pruebas y Prácticas BLE con ESP32

Este repositorio contiene una serie de prácticas relacionadas con la implementación de comunicación Bluetooth Low Energy (BLE) utilizando un ESP32. Cada práctica explora un aspecto específico de BLE, desde el emparejamiento básico hasta la reconexión automática y la transmisión de comandos.

## Tecnologías Utilizadas

- **ESP32**: Microcontrolador con capacidades BLE y WiFi.
- **Bluetooth Low Energy (BLE)**: Tecnología de comunicación inalámbrica de baja energía que permite la conexión de dispositivos con bajo consumo de batería.
- **PlatformIO**: Entorno de desarrollo utilizado para compilar y cargar los proyectos en el ESP32.
- **C++**: Lenguaje de programación utilizado para desarrollar las aplicaciones BLE en el ESP32.

## Descripción de las Prácticas

### 1. Emparejar ESP32 con BLE
En esta práctica, se implementa un servidor BLE en el ESP32 que permite emparejarse con dispositivos clientes. La práctica se centra en la configuración básica de un servidor BLE, la creación de un servicio y una característica BLE.

**Objetivos:**
- Iniciar el servidor BLE.
- Establecer un servicio y una característica BLE.
- Permitir la conexión desde dispositivos clientes.

### 2. Transmisión de Comandos con ESP32
Esta práctica permite la transmisión de comandos desde el ESP32 hacia un dispositivo cliente BLE. Se envían datos de forma periódica a los dispositivos conectados mediante notificaciones.

**Objetivos:**
- Configurar notificaciones BLE.
- Enviar datos periódicamente a un cliente BLE conectado.
- Probar la transmisión de comandos desde el ESP32 hacia un cliente.

### 3. Desconexión y Reconexion Automática
Aquí se prueba el manejo de la desconexión y reconexión automática de un cliente BLE. El ESP32 está configurado para reanudar la publicidad BLE cuando un dispositivo se desconecta y permitir que se reconecte automáticamente.

**Objetivos:**
- Detectar desconexiones de un cliente BLE.
- Reiniciar la publicidad para permitir la reconexión.
- Probar la reconexión automática de un dispositivo cliente.

### 4. Parámetros de Conexión BLE
En esta práctica se exploran los ajustes de los parámetros de conexión BLE, como el intervalo de publicidad y los intervalos de conexión. El objetivo es optimizar el rendimiento de la conexión BLE para diversas situaciones.

**Objetivos:**
- Ajustar los parámetros de publicidad BLE.
- Modificar los intervalos de conexión y otros parámetros relacionados.
- Realizar pruebas de estabilidad y optimización de la conexión.

## Cómo Probar las Prácticas

1. **Instalar PlatformIO**: Asegúrate de tener instalado PlatformIO en tu entorno de desarrollo.
2. **Compilar y subir el código**: Cada práctica está preparada para ser compilada y subida al ESP32 usando PlatformIO.
3. **Monitor serie**: Utiliza el monitor serie para ver la información sobre el estado de las conexiones BLE y los mensajes de depuración.
4. **Aplicación BLE**: Utiliza una aplicación BLE como **nRF Connect** o **LightBlue** para conectarte al ESP32 y probar las funcionalidades.

## Licencia

Este proyecto está bajo la Licencia MIT. Puedes utilizar, modificar y distribuir el código libremente, siempre y cuando se incluya la atribución correspondiente.
