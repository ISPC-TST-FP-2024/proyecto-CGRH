# Tecnicatura Superior en Telecomunicaciones
### Profesores: Gonzalo Vera, Jorge Morales, Dante Violi  

## Informacion General

***La carpeta contiene toda la información relacionada con los prototipos de los sensores y sus respectivas simulaciones. En esta carpeta se encuentran los datasheets de cada sensor, las conexiones implementadas, así como el proyecto de PlatformIO para el desarrollo y programación del sistema. Además, se incluyen los archivos de simulación en Proteus para cuando no se pueda simular con PlatformIO , acompañados de las conclusiones obtenidas a partir de estas pruebas, los datos registrados, los valores medidos y si se puede un video demostrativo que muestra el funcionamiento del sistema y cómo se emplea en la práctica.***  

## Módulos de Comunicación Configurados y Conectados al ESP8266

### Hardware Utilizado:

ESP8266: Módulo con Wi-Fi integrado, utilizado para conectarse a una red y enviar solicitudes HTTP.

### Protocolos de Comunicación Configurados

#### Protocolo Utilizado:

HTTP (HyperText Transfer Protocol): Este protocolo permite la comunicación entre el ESP8266 y un servidor web mediante solicitudes HTTP.

#### Librerías Utilizadas:

- ESP8266WiFi.h: Librería para conectarse a redes Wi-Fi.
- ESP8266HTTPClient.h: Librería para hacer solicitudes HTTP (GET y POST).

### Pruebas Iniciales de Comunicación Realizadas

#### Prueba 1: Conexión a la red Wi-Fi

Procedimiento:

- Configura el ESP8266 para conectarse a la red Wi-Fi especificada.
- Verifica que el ESP8266 obtenga una dirección IP local.

Resultados:
- El ESP8266 se conectó exitosamente a la red Wi-Fi.
- En el Monitor Serie, aparece el mensaje "Conectado con éxito, IP asignada: [dirección IP]".

#### Prueba 2: Envío de datos al servidor
Procedimiento:

-Envía una solicitud HTTP POST con los datos user y pass al servidor web.
-Verifica que el servidor reciba los datos y responda adecuadamente.

Resultados:

- El código HTTP devuelto fue 200 (OK), indicando que la solicitud fue exitosa.
- El ESP8266 muestra la respuesta del servidor en el Monitor Serie.

## Documentación de la Configuración de Comunicación y Resultados de Pruebas

#### Configuración:
Conexión Wi-Fi:

Se utilizó la función WiFi.begin() para conectarse a la red Wi-Fi usando el SSID y contraseña especificados.  
El ESP8266 verifica continuamente el estado de la conexión con WiFi.status() hasta que se establece correctamente.  

Solicitud HTTP:  

Se utilizó la librería ESP8266HTTPClient para realizar solicitudes HTTP POST al servidor.
Los datos se enviaron en el formato application/x-www-form-urlencoded mediante la cabecera de la solicitud.

Resultados de Pruebas: 

Conectividad Wi-Fi: El ESP8266 se conectó exitosamente a la red Wi-Fi y se le asignó una dirección IP.
Comunicación HTTP: Las solicitudes HTTP POST fueron enviadas correctamente al servidor, y se recibieron las respuestas correspondientes.

Conclucion:

El código puede adaptarse para enviar diferentes tipos de datos, incluyendo valores de sensores o información de estado del dispositivo.
Se puede agregar manejo de errores más robusto para situaciones en las que el servidor no esté disponible o el Wi-Fi se desconecte.

## Actualizacion
20240919
Se actualizo Readme.

