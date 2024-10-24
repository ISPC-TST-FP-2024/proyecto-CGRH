from flask import Flask, request, jsonify
import mysql.connector
from prettytable import PrettyTable  # Para mostrar los datos en formato tabla

app = Flask(__name__)

# Configuración de conexión a MySQL en el servidor remoto
db_config = {
    'host': 'gonaiot.com',
    'port': 3310,  # Puerto mapeado en el contenedor
    'user': 'opalo_user',
    'password': 'opalo_password',
    'database': 'iot_project_opalo'
}

# Ruta para recibir datos del ESP32
@app.route('/api', methods=['POST'])
def recibir_datos():
    try:
        # Obtener los datos enviados por el ESP32
        nodo_id = request.form['id']
        temperatura = request.form['temp']
        humedad = request.form['hum']
        luz_ambiente = request.form['luz']
        humedad_suelo_cap = request.form['hum_cap']
        humedad_suelo_res = request.form['hum_res']
        nivel_agua = request.form['nivel_agua']
        nombre = request.form['nombre']
        apellido = request.form['apellido']

        # Conexión a la base de datos
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor()

        # Verificar si el dispositivo ya existe en la base de datos
        sql_dispositivo = """
            SELECT id_dispositivo FROM dispositivo
            WHERE nombre = %s AND apellido = %s
        """
        cursor.execute(sql_dispositivo, (nombre, apellido))
        dispositivo = cursor.fetchone()

        # Si el dispositivo no existe, lo insertamos
        if dispositivo is None:
            sql_insert_dispositivo = """
                INSERT INTO dispositivo (nombre, apellido)
                VALUES (%s, %s)
            """
            cursor.execute(sql_insert_dispositivo, (nombre, apellido))
            conexion.commit()
            dispositivo_id = cursor.lastrowid  # ID del nuevo dispositivo
        else:
            dispositivo_id = dispositivo[0]  # ID del dispositivo existente

        # Insertar los datos en la tabla sensor_datos
        sql_sensor_datos = """
            INSERT INTO sensor_datos (nodo_id, temperatura, humedad, luz_ambiente,
                                      humedad_suelo_cap, humedad_suelo_res, nivel_agua, dispositivo_id)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
        """
        datos_sensor = (
            nodo_id, temperatura, humedad, luz_ambiente,
            humedad_suelo_cap, humedad_suelo_res, nivel_agua, dispositivo_id
        )
        cursor.execute(sql_sensor_datos, datos_sensor)
        conexion.commit()

        cursor.close()
        conexion.close()

        return jsonify({'status': 'Datos guardados correctamente'}), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al guardar los datos', 'error': str(e)}), 500

# Función para mostrar datos en formato tabla
def mostrar_tabla(cursor, query, params=()):
    cursor.execute(query, params)
    rows = cursor.fetchall()
    if rows:
        table = PrettyTable()
        table.field_names = [i[0] for i in cursor.description]
        for row in rows:
            table.add_row(row)
        print(table)
    else:
        print("No se encontraron datos.")

if __name__ == '__main__':
    # Ejecutar la API Flask
    app.run(host='0.0.0.0', port=5000, debug=True)
