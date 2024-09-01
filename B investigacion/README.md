
<p align=center><img src="../E recursos/image1-8.png" width="900"></p>

### Informacion General
Se crearon carpetas específicas para mejorar la agilidad durante la investigación en cada uno de los Sprints. Para cada Sprint, se implementaron 4 carpetas con el objetivo de organizar mejor la información y optimizar el flujo de trabajo al añadir los datos complementarios.  
 Esto facilita un acceso más rápido y eficiente a la documentación relevante, asegurando que los avances se integren de manera coherente en cada etapa del proyecto.  

Carpeta: ***B Investigación***
### Investigación
***
__La carpeta "B Investigación" alberga el material y los documentos relacionados con la investigación en curso. Aquí se recopilan todos los elementos esenciales para el desarrollo y análisis del proyecto, incluyendo:__  

__Documentación de Investigación:__ Informes, artículos, y recursos que sustentan el marco teórico y los fundamentos del estudio.  

__Datos Recopilados:__ Resultados de encuestas, experimentos, y otras fuentes de datos relevantes.  

__Análisis y Resultados:__ Interpretación de datos, gráficos, y conclusiones derivadas de la investigación.  

__Metodología:__ Descripción detallada de los métodos y enfoques utilizados en el proceso investigativo.  

__Referencias:__ Citas y bibliografía de fuentes consultadas durante la investigación.   
***

### Recursos
Software 💻
```
Visualizador de PDF.
Visualizador de word.
```
***
### Objetivos

__Centralizar Información:__ Organizar y almacenar toda la documentación y datos relevantes de la investigación en un solo lugar para facilitar el acceso y la gestión.  

__Facilitar el Análisis:__ Provee una estructura ordenada que permita una revisión eficiente y un análisis detallado de la información recopilada.  

__Documentar Metodología y Procedimientos:__ Registra los métodos, técnicas y procedimientos utilizados en la investigación para asegurar la transparencia y la replicabilidad del estudio.  

__Asegurar la Integridad de los Datos:__ Mantiene la integridad y la precisión de los datos recopilados, garantizando que se conserven de manera segura y accesible.  

__Proveer Referencias Completas:__ Incluir todas las fuentes y referencias consultadas para ofrecer un respaldo sólido a los hallazgos y conclusiones del estudio.  

__Facilitar la Comunicación:__ Sirve como un recurso centralizado para la comunicación y colaboración entre los miembros del equipo de investigación.  

__Apoyar la Documentación Final:__ Contribuir a la elaboración de informes, presentaciones y publicaciones finales al proporcionar toda la información necesaria de manera organizada.  
***
## Estado  
**Fecha**: 30 de Agosto de 2024  
**Sprint**: 1  
**Historia de usuario**: uh#3  

## Actualizacion
***
**20240815**   
Se actualizo Readme. 
se agrego investigacion para debatir en la proxima reunion.  
los subi en word por que falta mas informacion por favor revisar y corregir.   
**20240820**  
Se implementaron 4 carpetas por Sprint para mejorar la organización y agilizar el proceso de investigación, facilitando el acceso y la integración de los datos en cada etapa del proyecto.  
***
**20240830**  
Se debe actualizar la informacion de las carpetas de acuerdo a los siguientes detalles (datasheet de sensores y actuadores. Protocolos spi, i2c):  

![Conexiones](../E%20recursos/Conexion%20fp_controlador_cultivo.png)

**Entradas Analógicas y Digitales:**  

1.	Sensores de Humedad del Suelo (HW-080) (x3):
o	Sensor 1: GPIO36 (ADC1_CHANNEL_0)
o	Sensor 2: GPIO39 (ADC1_CHANNEL_3)
o	Sensor 3: GPIO34 (ADC1_CHANNEL_6)
2.	DHT11 (Temperatura y Humedad):
o	GPIO14 (Digital)
3.	Sensor de Lluvia (AB119):
o	GPIO33 (Digital)
4.	Sensor Ultrasónico (HC-SR04):
o	Trigger: GPIO12
o	Echo: GPIO13
5.	LDR (Luz Ambiente):
o	GPIO32 (ADC1_CHANNEL_4)
6.	Micrófono Electret:
o	GPIO35 (ADC1_CHANNEL_7)
7.	Sensores PIR (HCSR501) (x3):
o	Sensor 1: GPIO25
o	Sensor 2: GPIO26
o	Sensor 3: GPIO27  

**Salidas:**
1.	Tira LED WS2812B:
o	GPIO15 (Digital)
2.	Módulo de Relé de 4 Canales:
o	Canal 1 (Bomba de Agua): GPIO4
o	Canal 2 (Válvula 1): GPIO16
o	Canal 3 (Válvula 2): GPIO17
o	Canal 4 (Válvula 3): GPIO0  

**Interfaces de Comunicación:**
SPI:  
-	MOSI: GPIO23
-	MISO: GPIO19
-	SCK: GPIO18
-	SS (NSS): GPIO5  
I2C:  
-	SCL: GPIO22
-	SDA: GPIO21  
  
**Distribucion de Componentes**  

![Distribucion de componentes](../E%20recursos/Instalacion%20Fisica%20de%20Sensores%20y%20Actuadores.png)  
  
**20240831**  
## Simulacion en wokwi de la conexion de los sensores y actuadores.  
La siguinete pagina indica como realizar la simulacion en el ide VSCode con la extension de wokwi. 
[Simulacion en wokwi](https://docs.wokwi.com/vscode/getting-started).  
Esta informacion es importante para entender como se utiliza el repositorio auxiliar de desarrollo: [Repositorio auxiliar de desarrollo](https://github.com/ISPC-TST-FP-2024/controlador_gmrh.git)

## Simulacion en proteus de la conexion de los sensores y actuadores.  
Nos sirve de soporte para la simulacion de los componentes electronicos. Ademas los componentes que no soporten la simulacion en wokwi se pueden simular en proteus. Recordar que proteus no soporta a la fecha agosto/2024 al modulo ESP-32, sin embargo al trabajar con el framework de arduino podemos utilizarlo para el firmware del ESP-32.   
  
## Otros simuladores
- [Tinkercad](https://www.tinkercad.com/)
Tinkercad es un simulador en línea gratuito de Autodesk que permite a los usuarios diseñar y simular circuitos electrónicos y proyectos de programación.



