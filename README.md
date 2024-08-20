
![alt text](/caratula.png)  

# Tecnicatura Superior en Telecomunicaciones
### Profesores: Gonzalo Vera, Jorge Morales, Dante Violi  
### Alumnos: 
- Jose Marquez, GitHub: [@Jose Marquez](https://github.com/marquezjose).
- Luciano Lujan, GitHub: [@Luciano Lujan](https://github.com/lucianoilujan).
- Lisandro Juncos, GitHub: [@Lisandro Juncos](https://github.com/Lisandro-05).
- Tiziano Paez, GitHub: [@tpaez](https://github.com/tpaez).
- Marcos Bordón, GitHub: [@Marcos-BR-03](https://github.com/Marcos-BR-03).
- Karina Jazmin Barbero, GitHub: [@karina-lolis](https://github.com/karina-lolis).
- Nicolás Nahuel Barrionuevo, GitHub: [@NicolasBa27](https://github.com/NicolasBa27).
- Macarena Aylen Carballo, GitHub: [@MacarenaAC](https://github.com/MacarenaAC).
- Diego Ares, GitHub: [@diegote7](https://github.com/diegote7).
- Fernando Gimenez Coria, GitHub: [@FernandoGC](https://github.com/FerCbr).
- Raul Antonio Jara, GitHub: [@r-j28](https://github.com/r-j28).
- Vittorio Durigutti, GitHub: [@Vittorio Dirigutti](https://github.com/vittoriodurigutti).  
- Joaquin Zalazar, GitHub: [@Joaquin-Zalazar](https://github.com/breaakerr).  
- Patricio Leandro Roldan, Github:  [@pleroldan](https://github.com/pleroldan).
- Romina Huk,  Github:  [@RoHu17](https://github.com/RoHu17).
- Nahuel Vélez, GitHub: [@Nahuelvelez](https://github.com/Nahuelvelez).
- Paola Natalia Alejandra Pantoja, Github:[@PaolaaPantoja](https://github.com/PaolaaPantoja).
- Laura Analia Brizuela, GitHub:[@gerbena03] (https://github.com/gerbena03).

### La Formación Profesional
 
El trayecto formativo de "Desarrollador de Dispositivos IoT" busca formar técnicos capacitados para desempeñarse en todas las capas del Internet de las Cosas (IoT), desarrollando, administrando y manteniendo proyectos de IoT. Esto implica:

• Desarrollo de dispositivos para el IoT  
• Configuración y administración de redes IoT   
• Integración y gestión de datos en sistemas IoT  
• Implementación de medidas de seguridad en dispositivos y redes IoT  
### Informacion General
***
Extructura pedida por el profesor  
• En la carpeta ***"A Requisitos":*** se encuentran los requisitos de la tarea.   
• En la carpeta ***"B Investigación":*** se encuentran las investigaciones sobre la tarea pedida.  
• En la carpeta ***"C Prototipo":*** se encuentran las primeras implementaciones de las 2 carpetas anteriores.   
• En la carpeta ***"D presentación":*** se encuentran la presentación del trabajo concluido.
• En la carpeta ***"E Recursos":*** se encuentran los archivos para la estructura ABP.  


### FP: Desarrollador de Dispositivos IoT
 
# Resumen del FP: Desarrollador de Dispositivos IoT  

## Proyecto Central:   
Desarrollar un sistema de control y monitoreo distribuido para optimizar el uso y gestión del agua en diferentes entornos. Este controlador, tipo célula, es capaz de abarcar el control general y amplio de jardines, plazas, huertas urbanas, así como grandes plantaciones agrícolas en campos rurales. El sistema se enfoca en la eficiencia y sostenibilidad del riego mediante la gestión y monitoreo inteligente de los recursos hídricos locales.
 

# Componentes del Proyecto:

### Hardware:
• Microcontroladores: ESP32  
• Módulos de Comunicación: LoRa  
• Sensores: Humedad del suelo, PH, lluvia, temperatura, etc.  
• Actuadores: Bombas, sistemas de iluminación, motores de posicionamiento  

### Software:
• IDE y Herramientas de Desarrollo: VSCode, PlatformIO, Git, GitHub  
• Lenguajes de Programación: C++, Arduino framework  
• Metodologías: ABP (Aprendizaje Basado en Proyectos), Kanban,Scrum, Agile  

### Protocolos de Comunicación:
• UART, SPI, I2C: Comunicación entre sensores y microcontroladores
• WiFi/Bluetooth: Conectividad para ESP32
• MQTT: Protocolo de comunicación para IoT
• HTTP/HTTPS: Integración con servidores web y APIs REST
• TCP, UDP, IPv6, OpenThread, Matter, Thread, Zigbee, LoRa Visualización:  
• Interfaces de Usuario: Paneles de control basados en web utilizando herramientas como Node-RED, otros tipo HMI (LCD, OLED,etc)  
• Visualización de Datos: Opciones provistas por docentes desde el cloud  
## Recursos

```
 Tinkercad
 VSCode
 PlatformIO 
 Wokwi
 C/C++
 MicroPython.
 Proteus
```
## Objetivos
***
### Funcionamiento del Sistema
1.Recolección de Datos:
• Sensores: Los sensores instalados recolectan datos sobre variables ambientales críticas como humedad del suelo,niveles de pH, precipitaciones y temperatura.  
• Microcontroladores ESP32: Los microcontroladores ESP32reciben datos de los sensores a través de interfaces de comunicación como UART, SPI e I2C.  

### 2.Transmisión de Datos:
• Módulos LoRa: Utilizando módulos de comunicación LoRa, los microcontroladores ESP32 transmiten los datos recolectados a una estación base o a un servidor central.  
• WiFi/Bluetooth: Alternativamente, la comunicación puede realizarse mediante WiFi o Bluetooth, dependiendo de la infraestructura y el alcance requerido.  

### 3.Procesamiento de Datos:
• Servidor Central/Estación Base: Un servidor central procesa los datos recibidos, analizando las condiciones ambientales y generando informes en tiempo real.  
• MQTT y HTTP/HTTPS: Los datos son enviados y recibidos mediante protocolos MQTT para asegurar una comunicación eficiente y segura. Las integraciones con APIs REST permiten la interoperabilidad con otras plataformas y servicios.  

### 4.Toma de Decisiones y Actuación:
• Algoritmos de Control: Basados en los datos procesados, los algoritmos de control toman decisiones para optimizar el riego.
• Actuadores: Los microcontroladores ESP32 envían comandos a los actuadores (bombas, sistemas de iluminación, motores de posicionamiento) para ejecutar las acciones necesarias, comoactivar el riego o ajustar la iluminación.  

### 5.Visualización y Monitoreo:
• Paneles de Control Web: Los usuarios pueden monitorear y controlar el sistema a través de interfaces de usuario web, utilizando herramientas como Node-RED.  
• Visualización en Cloud: Los datos también pueden ser visualizados en plataformas cloud, proporcionando accesibilidad remota y almacenamiento seguro de los datos históricos.  
***

## Actualizacion
***
### Semana 1: Definición de Requerimientos y Planificación Inicial  
Materia Responsable: Redes  
Objetivo de la Semana: Definir la arquitectura de red, planificar la comunicación, identificar variables y definir conceptos básicos del proyecto IoT.  

### Actividades:
Reunión inicial para discutir el alcance del proyecto y asignación de roles y responsabilidades.  ✔   
Investigación y documentación de métodos y protocolos de comunicación (LoRa, MQTT).  ✔   
Identificación y listado de variables a sensorizar (humedad del suelo, pH, lluvia, temperatura).  ✔   

Diseño inicial de la arquitectura de red.  ✖  
Configuración de repositorios Git y GitHub. ✔   
Creación de un cronograma de hitos importantes y sistema de seguimiento de tareas (Kanban).  ✖  
***
**uh1tk19** Documentación de roles y responsabilidades.
  
  A continuación se detalla gráficamente la asignación de roles para el equipo. 

  <center><img src="./E recursos/EQUIPO SCRUM.jpg" width="800"></center>
