# Tecnicatura Superior en Telecomunicaciones  

## Asignaturas: 
- Electronica Microcontroada. Profesor **Cristian Gonzalo Vera**
- Sensores y Actuadores. Profesor **Jorge Morales**
- Redes. Profesor **Dante Violi**
  
  
## Descripción general:    
 
El AHT10 es un sensor de temperatura y humedad de alta precisión que utiliza el protocolo I2C para la comunicación. Es ideal para aplicaciones que requieren mediciones precisas de temperatura y humedad con bajo consumo de energía. El sensor puede operar en un rango de temperaturas de -40°C a 85°C y mide humedad relativa del 0% al 100%.

## Especificaciones técnicas principales:  
●Voltaje de operación: 2.0V - 5.5V  
●Protocolo de comunicación: I2C  
●Rango de medición de humedad: 0% - 100% RH  
●Precisión de humedad: ±2% RH  
●Rango de medición de temperatura: -40°C a 85°C  
●Precisión de temperatura: ±0.3°C  
●Frecuencia de comunicación I2C: Hasta 400 kHz 

## Conexión del sensor AHT10:  
Pin AHT10---Conexión ESP32  
VCC-----------3.3v  
GND-----------GND   
SDA-----------GPIO21 (SDA)  
SCL-----------GPIO22 (SCL)  


## Preguntas para verificar las pruebas de funcionamiento y efectividad:    
¿Está recibiendo el ESP32 los datos correctamente a través del protocolo I2C?

¿Se están obteniendo valores precisos de temperatura y humedad en condiciones normales?

¿Los valores se mantienen estables con cambios en las condiciones ambientales?  

¿La comunicación I2C es lo suficientemente rápida para la aplicación?  

¿Qué impacto tiene el sensor en el consumo de energía del sistema?

### Conclusiones de las pruebas:  
