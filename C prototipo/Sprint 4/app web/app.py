# app.py
from flask import Flask, request, jsonify, render_template
from db import ejecutar_consulta, insertar_datos

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

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

        # Verificar si el dispositivo ya existe en la base de datos
        sql_dispositivo = """
            SELECT id_dispositivo FROM dispositivo
            WHERE nombre = %s AND apellido = %s
        """
        dispositivo = ejecutar_consulta(sql_dispositivo, (nombre, apellido))

        if not dispositivo:
            # Si el dispositivo no existe, lo insertamos
            sql_insert_dispositivo = """
                INSERT INTO dispositivo (nombre, apellido)
                VALUES (%s, %s)
            """
            insertar_datos(sql_insert_dispositivo, (nombre, apellido))
            # Obtener el ID del nuevo dispositivo
            dispositivo_id = ejecutar_consulta(sql_dispositivo, (nombre, apellido))[0]['id_dispositivo']
        else:
            dispositivo_id = dispositivo[0]['id_dispositivo']

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
        insertar_datos(sql_sensor_datos, datos_sensor)

        return jsonify({'status': 'Datos guardados correctamente'}), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al guardar los datos', 'error': str(e)}), 500

# Ruta para obtener los últimos 10 datos
@app.route('/api/datos', methods=['GET'])
def obtener_datos():
    try:
        # Consulta de los últimos 10 registros de la base de datos
        sql_consulta_datos = """
            SELECT nodo_id, temperatura, humedad, luz_ambiente, humedad_suelo_cap, 
                   humedad_suelo_res, nivel_agua, dispositivo_id
            FROM sensor_datos
            ORDER BY id DESC
            LIMIT 10
        """
        datos = ejecutar_consulta(sql_consulta_datos)

        return jsonify(datos), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener datos', 'error': str(e)}), 500

if __name__ == '__main__':
    # Ejecutar la API Flask
    app.run(host='0.0.0.0', port=5001, debug=True)
