# Tecnicatura Superior en Telecomunicaciones  

## Asignaturas: 
- Electronica Microcontroada. Profesor **Cristian Gonzalo Vera**
- Sensores y Actuadores. Profesor **Jorge Morales**
- Redes. Profesor **Dante Violi**
  
## Formacion Profesional
**Desarrollador de Dispositivos IoT**

## Descripcion del Respositorio  
Este repositorio es creado con el fin de dar soporte al desarrollo del proyecto final para la obtencion de la FP. 
El mismo esta organizado sobre una estructura de **platformIO** sobre el ide de **Visual Studio Code**. Tambien se agrega la extension de **wokwi** para la simulacion de los dispositivos. Y la carpeta **proteus** para la simulacion de los circuitos electronicos no soportados en wokwi.

## Descripcion del Proyecto
El proyecto consiste en un sistema de control y monitoreo distribuido para optimizar el uso y gestión del agua en diferentes entornos.
Este controlador, tipo célula, es capaz de abarcar el control general y amplio de jardines, plazas, huertas urbanas, así como grandes plantaciones agrícolas en campos rurales.
El sistema se enfoca en la eficiencia y sostenibilidad del riego mediante la gestión y monitoreo inteligente de los recursos hídricos locales.  

El proyecto será llevado a cabo  a lo largo de 4 Sprints:  

- Sprint 1: Planificación y Configuración Inicial
- Sprint 2: Integración y Desarrollo de Software
- Sprint 3: Configuración Avanzada y Optimización
- Sprint 4: Prueba Final, Documentación y Presentación  

## Integrantes del Proyecto
- Jose Marquez, GitHub: [@marquezjose](https://github.com/marquezjose).
- Luciano Lujan, GitHub: [@lucianoilujan](https://github.com/lucianoilujan).
- Vittorio Durigutti, GitHub: [@vittoriodurigutti](https://github.com/vittoriodurigutti).
- Fernando Gimenez Coria, GitHub: [@FerCbr](https://github.com/FerCbr).
- Tiziano Paez, GitHub: [@tpaez](https://github.com/tpaez).
- Marcos Bordón, GitHub: [@Marcos-BR-03](https://github.com/Marcos-BR-03).
- Karina Jazmin Barbero, GitHub: [@karina-lolis](https://github.com/karina-lolis).
- Nicolás Nahuel Barrionuevo, GitHub: [@NicolasBa27](https://github.com/NicolasBa27).
- Macarena Aylen Carballo, GitHub: [@MacarenaAC](https://github.com/MacarenaAC).
- Diego Ares, GitHub: [@diegote7](https://github.com/diegote7).
- Lisandro Juncos, GitHub: [@Lisandro-05](https://github.com/Lisandro-05).
- Raul Antonio Jara, GitHub: [@r-j28](https://github.com/r-j28).
- Joaquin Zalazar, GitHub: [@breaakerr](https://github.com/breaakerr).  
- Patricio Leandro Roldan, Github: [@pleroldan](https://github.com/pleroldan).
- Romina Huk,  Github: [@RoHu17](https://github.com/RoHu17).
- Nahuel Vélez, GitHub: [@Nahuelvelez](https://github.com/Nahuelvelez).
- Paola Natalia Alejandra Pantoja, Github: [@PaolaaPantoja](https://github.com/PaolaaPantoja).
- Laura Analia Brizuela, GitHub: [@gerbena03](https://github.com/gerbena03).
- Joaquin Garzón, GitHub: [@Joacogarzonn](https://github.com/Joacogarzonn)  

---  
### El stack tecnologico utilizado en el proyecto es el siguiente:
- **Plataforma de Hardware:** ESP32
- **ide:** Visual Studio Code
- **Lenguaje de Programacion:** C++, basado en el framework de arduino
- **Plataforma de Software:** PlatformIO, con el framework de arduino
- **Simulacion:** Wokwi y proteus
- **Control de Versiones:** GitHub
- **Documentacion:** Markdown
- **Gestion de Proyecto:** kanban en GitHub
- **Comunicacion:** Discord

### Etapa del Proyecto  
- **Sprint 1:** Planificacion y Configuracion Inicial
- **Fecha de Inicio:** 31/08/2024

#### Actividades a completar:  

- Realización de pruebas iniciales de sensores.
- Realización de pruebas iniciales de actuadores.
- Configuración de librerías necesarias en ESP32.
- Documentación de los pasos de instalación.
- Registro de resultados de pruebas iniciales.
- Ajustes y calibraciones necesarias.
- Preparación de un informe de pruebas iniciales.
- Presentación de los resultados de pruebas al equipo.  



### Consideraciones sobre la Simulacion con wokwi  
Para la simulacion de los dispositivos se utiliza la extension de **wokwi** en **Visual Studio Code** debe tener en cuenta lo siguiente: 
- Tener instalada la extension wokwi en su Visual Studio Code.
- El archivo diagram.json corre la simulacion y es cambiado a .txt, para anularla. Si quiere correr la simulacion debe cargar apropiadamente el .json y cambiar la extension. 
- El archivo wokwi.toml es el archivo de configuracion de la extension wokwi.  

### Consideraciones sobre la Simulacion con Proteus  
Para la simulacion de los circuitos electronicos no soportados en wokwi se utiliza el software **Proteus**. En dicha carpeta se encuentra el proyecto, cargado en la version 8.12. Ademas se agrega la organizacion de los tests correspondientes a cada dispositivo. 
Se debe tener en cuenta que proteus no simula a la fecha agosto/2024 los dispositivos ESP32, por lo que la simulacion se basa en el arduino uno. Y se utiliza luego el firmware desarrollado para el ESP32.

## Descripción general:  

El Módulo Sensor de Luz con LDR (Fotoresistor) es un dispositivo utilizado para medir la intensidad de la luz en un entorno. El LDR (Light Dependent Resistor) cambia su resistencia en función de la cantidad de luz que incide sobre él. Este módulo es ideal para aplicaciones donde es necesario detectar niveles de iluminación o activar dispositivos en función de la luz ambiental.

## Especificaciones técnicas principales:  

●Rango de voltaje de operación: 3.3V a 5V DC  
●Tipo de sensor: LDR (Fotoresistor)  
●Tipo de salida: Analógica  
●Rango de resistencia del LDR: Varía de 1kΩ (alta luz) a 10kΩ (baja luz)  
●Precisión: Depende de la resolución del ADC (convertidor analógico a digital) del microcontrolador.  

## Preguntas para verificar las pruebas de funcionamiento y efectividad:  

¿El módulo LDR proporciona una salida analógica proporcional a la intensidad de la luz?  

¿La resolución del ADC del microcontrolador es suficiente para medir los cambios en la luz?  

¿El módulo responde de manera consistente a diferentes niveles de iluminación?  

¿El módulo se integra fácilmente con el microcontrolador?  

¿Existen interferencias o ruidos en la señal analógica proporcionada por el LDR?  

¿El módulo funciona correctamente en el rango de voltaje especificado (3.3V a 5V)?

## Conclusiones de las pruebas:  

