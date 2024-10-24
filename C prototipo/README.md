## Informacion General
***
### Carpeta: ***D Prototipo*** 

__La carpeta "C Prototipo" esta toda la documentación y materiales relacionados con el desarrollo y evaluación del prototipo. En esta carpeta se incluyen:__  

__Diseño y Planificación:__ Planos, esquemas, y especificaciones técnicas del prototipo, junto con la planificación del proceso de desarrollo.    

__Documentación del Desarrollo:__ Registros detallados de cada etapa del proceso de construcción, incluyendo materiales utilizados, técnicas aplicadas, y modificaciones realizadas.  

__Resultados de Pruebas:__ Informes y datos derivados de las pruebas realizadas al prototipo, incluyendo análisis de rendimiento y cualquier ajuste necesario.  

__Problemas y Soluciones:__ Descripción de problemas encontrados durante el desarrollo y las soluciones implementadas para resolverlos.  

__Referencias y Recursos:__ Cualquier recurso adicional, como manuales, guías técnicas y referencias relevantes para el desarrollo del prototipo.
***


## Recursos
#### Software 💻

**Entorno de Desarrollo:**  
**• VSCode:** Para escribir y gestionar el código.
PlatformIO: Para facilitar el desarrollo con ESP32 y otros microcontroladores.
Lenguaje de Programación:

**• C/C++:** Común para la programación de microcontroladores.
Python: Para scripts de procesamiento de datos o control.

**Bibliotecas y Frameworks:**  
**• Arduino Libraries:** Para trabajar con sensores y módulos específicos.
ESP-IDF o Arduino Core para ESP32: Para programación específica del ESP32.  

**Herramientas de Comunicación:**  
**• MQTT Broker:** Para la comunicación entre dispositivos y el servidor central.
Protocolos de Comunicación: Implementación de MQTT, HTTP/HTTPS para enviar y recibir datos.

**Visualización y Control:**  
**• Interfaz Web:** Para monitorear y controlar el sistema desde un navegador (puedes usar frameworks como React, Vue.js, o simplemente HTML/CSS/JavaScript).
Plataformas en la Nube: AWS, Azure, o Google Cloud para almacenar datos y manejar la visualización en la nube.

**Control de Versiones:**  
**• Git:** Para el control de versiones del código y la colaboración en el desarrollo (usualmente acompañado de GitHub, GitLab o Bitbucket).


#### Hardware ⚙

**Microcontroladores:**  
**• ESP32:** Ideal por su conectividad (WiFi y Bluetooth) y capacidad de procesamiento.

**Sensores:**  
**• Sensor de Humedad del Suelo:** Para medir la humedad en el suelo.  
**• Sensor de pH:** Para medir el pH del suelo o del agua.  
**• Sensor de Lluvia:** Para detectar precipitaciones y ajustar el riego en consecuencia.  
**• Sensor de Temperatura:** Para medir la temperatura ambiental.

**Módulos de Comunicación:**  
**• Módulos LoRa:** Para comunicación de largo alcance, ideal en áreas rurales.  
**• Módulos Zigbee o Thread:** Para redes de sensores de corto a medio alcance.  

**Actuadores:**  
**• Válvulas de Riego:** Para controlar el flujo de agua.  
**• Bombas de Agua:** Si el sistema necesita bombear agua desde una fuente externa.

**Fuente de Energía:**  
**• Baterías o Paneles Solares:** Según la ubicación y la duración de funcionamiento necesario.

**Elementos de Soporte:**  
**• Cables y Conectores:** Para conectar sensores y actuadores a los microcontroladores.  
**• Caja de Protección:** Para resguardar los componentes electrónicos de condiciones ambientales.

## Objetivos

__Consolidar el Diseño del Prototipo:__ Agrupar toda la documentación relacionada con el diseño y desarrollo del prototipo.  

__Registrar el Proceso de Desarrollo:__ Documentar detalladamente cada etapa del proceso de construcción del prototipo, desde la concepción inicial hasta la implementación final, para asegurar una trazabilidad completa.

__Centralizar la Información Técnica:__ Mantener un archivo organizado con todos los datos técnicos, materiales utilizados, y configuraciones del prototipo, facilitando su análisis y futuras modificaciones.  

__Facilitar la Evaluación y Pruebas:__ Incluir los resultados de las pruebas realizadas al prototipo, así como cualquier ajuste o mejora implementada en base a ese protoripo.

__Documentar Problemas y Soluciones:__ Registrar cualquier Problemas encontrado durante el desarrollo del prototipo y las soluciones adoptadas.

__Apoyar la Comunicación y Colaboración:__ Sirve como un recurso central para los miembros del equipo, permitiendo un acceso fácil y claro a toda la información relevante del prototipo.  

## Estado
**Fecha**: 30 de Agosto de 2024  
**Sprint**: 1
**Historia de usuario**: uh#3  

## Avances 
***
20240815
Se actualizo Readme.  

*** 
01092024  
### Semana 3: UH#3 
#### Sprint Backlog - Sprint 1

- [x] 1. **Instalación física de sensores:** uh3tk1_2_3 completado. 
- [x] 2. **Instalación física de actuadores:** uh3tk4_5_6 completado.  
  
![Distribucion](../E%20recursos/Instalacion%20Fisica%20de%20Sensores%20y%20Actuadores.png)  
***  
  
- [x] 3. **Conexión de sensores al ESP32:** uh3tk7_8_9 completado.
- [x] 4. **Conexión de actuadores al ESP32:**  
  
![Conexiones](../E%20recursos/Conexion%20fp_controlador_cultivo.png)  
***  
  
- [x] 5. **Realización de pruebas iniciales de sensores:**
- [ ] 6. **Realización de pruebas iniciales de actuadores:**  

Se implementa las pruebas iniciales sobre el siguiente stack: 
- **ide:** VsCode
- **Lenguaje:** C/C++, con el framework de Arduino
- **Plataforma:** PlatformIO, con el core de Arduino para ESP32
- **simulacion:** wokwi, proteus, tinkercad.  

---  
- [ ] 7. **Configuración de librerías necesarias en ESP32:**
- [ ] 8. **Documentación de los pasos de instalación:**
- [ ] 9. **Registro de resultados de pruebas iniciales:**
- [ ] 10. **Ajustes y calibraciones necesarias:**
- [ ] 11. **Preparación de un informe de pruebas iniciales:**
- [ ] 12. **Presentación de los resultados de pruebas al equipo:**


