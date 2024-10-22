CREATE DATABASE IF NOT EXISTS `proyecto_iot` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `proyecto_iot`;

-- Tabla para almacenar datos de sensores
DROP TABLE IF EXISTS `sensor_datos`;
CREATE TABLE `sensor_datos` (
  `id_sensor` int NOT NULL AUTO_INCREMENT,
  `nodo_id` varchar(50) DEFAULT NULL,  -- ID del nodo (nodo1, nodo2, etc.)
  `temperatura` float DEFAULT NULL,    -- temperatura en grados Celsius
  `humedad` float DEFAULT NULL,        -- humedad relativa en %
  `luz_ambiente` float DEFAULT NULL,   -- nivel de luz ambiente
  `humedad_suelo_cap` int DEFAULT NULL,-- humedad del suelo capacitiva
  `humedad_suelo_res` int DEFAULT NULL,-- humedad del suelo resistiva
  `nivel_agua` int DEFAULT NULL,       -- nivel de agua en cm
  `tiempo_medicion` timestamp NULL DEFAULT CURRENT_TIMESTAMP,  -- tiempo de medición
  PRIMARY KEY (`id_sensor`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Tabla para almacenar datos de actuadores
DROP TABLE IF EXISTS `actuador_datos`;
CREATE TABLE `actuador_datos` (
  `id_actuador` int NOT NULL AUTO_INCREMENT,
  `nodo_id` varchar(50) DEFAULT NULL,   -- ID del nodo que acciona
  `tipo_actuador` varchar(50) DEFAULT NULL,  -- tipo de actuador (bomba, iluminación)
  `estado_actuador` varchar(20) DEFAULT NULL,-- estado del actuador (encendido, apagado)
  `hora_accion` timestamp NULL DEFAULT CURRENT_TIMESTAMP, -- hora de la acción
  `sensor_id` int DEFAULT NULL,          -- id del sensor relacionado
  PRIMARY KEY (`id_actuador`),
  KEY `fk_sensor` (`sensor_id`),
  CONSTRAINT `fk_sensor` FOREIGN KEY (`sensor_id`) REFERENCES `sensor_datos` (`id_sensor`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Insertar algunos datos de ejemplo
INSERT INTO `sensor_datos` 
(nodo_id, temperatura, humedad, luz_ambiente, humedad_suelo_cap, humedad_suelo_res, nivel_agua, tiempo_medicion) 
VALUES 
('nodo1', 22.1, 60.5, 300.2, 40, 30, 15, '2024-10-22 10:30:00'),
('nodo1', 23.3, 58.0, 320.4, 42, 32, 14, '2024-10-22 10:35:00');

INSERT INTO `actuador_datos` 
(nodo_id, tipo_actuador, estado_actuador, hora_accion, sensor_id) 
VALUES 
('nodo1', 'Bomba', 'Encendido', '2024-10-22 10:30:05', 1),
('nodo1', 'Iluminación', 'Apagado', '2024-10-22 10:30:05', 2);


-- Crear tabla 'dispositivo' para almacenar información de los dispositivos
CREATE TABLE `dispositivo` (
  `id_dispositivo` int NOT NULL AUTO_INCREMENT,  -- ID incremental del dispositivo
  `nombre` varchar(50) DEFAULT NULL,             -- Nombre de la persona
  `apellido` varchar(50) DEFAULT NULL,           -- Apellido de la persona
  PRIMARY KEY (`id_dispositivo`)                 -- Establecer id_dispositivo como clave primaria
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- Modificar la tabla 'sensor_datos' para agregar la columna dispositivo_id como clave foránea
ALTER TABLE `sensor_datos` 
ADD COLUMN `dispositivo_id` int DEFAULT NULL,   -- Agregar la columna dispositivo_id
ADD CONSTRAINT `fk_dispositivo_sensor` 
FOREIGN KEY (`dispositivo_id`) REFERENCES `dispositivo` (`id_dispositivo`);

-- Modificar la tabla 'actuador_datos' para agregar la columna dispositivo_id como clave foránea
ALTER TABLE `actuador_datos` 
ADD COLUMN `dispositivo_id` int DEFAULT NULL,   -- Agregar la columna dispositivo_id
ADD CONSTRAINT `fk_dispositivo_actuador` 
FOREIGN KEY (`dispositivo_id`) REFERENCES `dispositivo` (`id_dispositivo`);
