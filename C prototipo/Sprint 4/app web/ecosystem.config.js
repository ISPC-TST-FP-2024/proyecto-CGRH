/* 

PM2 
Sistema para levantar y permitir acceso remoto a la API usando esta PC como servidor
Archivo de configuración (útil para controlar entornos de desarrollo y producción) 

*/


module.exports = {
    apps: [
      {
        name: 'iot_api',
        script: 'app.py',            // Script principal de la aplicación
        interpreter: 'python',       // Intérprete de Python
        watch: true,                  // Reiniciar la aplicación en caso de cambios en el código
        env: {
          PORT: 5001,                 // Puerto donde correrá tu API
          FLASK_ENV: 'production'     // Variable de entorno para Flask
        }
      }
    ]
  };
  