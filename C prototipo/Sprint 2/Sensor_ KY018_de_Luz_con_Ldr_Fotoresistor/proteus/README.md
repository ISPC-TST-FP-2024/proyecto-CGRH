# Simulacion con proteus
## Consideraciones  
- Vamos a trabajar con la version proteus 8.12  
- Proteus no soporta la simulacion de ESP32, por lo que se simula con un arduino uno.
- Se debe tener en cuenta que la simulacion se basa en el firmware desarrollado para el ESP32.

## Organizacion 
- La carpeta proyecto contiene los proyectos de proteus para los tests de los componentes. La nomenclatura para los proyectos cargados en la carpeta ./proteus/proyecto es: 
    * version_nombre_componente.pdsprj  
    * version: Si la version es 1.0, el nombre es v1_0_nombre_componente.pdsprj  
- La carpeta ./proteus/test contiene los archivos de test de los componentes. La nomenclatura para sus archivos.cpp es: 
    * version_test_nombre_componente.cpp, donde nombre_componente debe estar asociado al proyecto de proteus en cuestion. 
    * version: Si la version es 1.0, el nombre es v1_0_test_nombre_componente.cpp