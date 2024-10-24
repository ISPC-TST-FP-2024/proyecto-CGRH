from flask import Flask, request, jsonify, render_template, send_file
import mysql.connector
import os
import pandas as pd
from io import BytesIO

app = Flask(__name__, template_folder="templates")

# Configuración de conexión a MySQL usando variables de entorno
db_config = {
    'host': os.getenv('MYSQL_HOST', 'gonaiot.com'),
    'port': int(os.getenv('MYSQL_PORT', 3310)),
    'user': os.getenv('MYSQL_USER', 'opalo_user'),
    'password': os.getenv('MYSQL_PASSWORD', 'opalo_password'),
    'database': os.getenv('MYSQL_DATABASE', 'iot_project_opalo')
}
# Ruta para servir el index.html
@app.route('/')
def index():
    try:
        return render_template('index.html')  # Renderiza la plantilla index.html
    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al cargar la página', 'error': str(e)}), 500

# 1. Ruta para traer todos los dispositivos (ID y nombre)
@app.route('/dispositivos', methods=['GET'])
def obtener_dispositivos():
    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor(dictionary=True)

        cursor.execute("SELECT id_dispositivo, nombre FROM dispositivo")
        dispositivos = cursor.fetchall()

        cursor.close()
        conexion.close()

        return jsonify(dispositivos), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener dispositivos', 'error': str(e)}), 500

# 2. Ruta para traer las mediciones de cada sensor para cada equipo
@app.route('/mediciones', methods=['GET'])
def obtener_mediciones():
    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor(dictionary=True)

        cursor.execute("""
            SELECT d.nombre, d.apellido, sd.* 
            FROM dispositivo d 
            JOIN sensor_datos sd ON d.id_dispositivo = sd.dispositivo_id
        """)
        mediciones = cursor.fetchall()

        cursor.close()
        conexion.close()

        return jsonify(mediciones), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener mediciones', 'error': str(e)}), 500

# 3. Ruta para traer la información del estado de cada actuador
@app.route('/actuadores', methods=['GET'])
def obtener_estado_actuadores():
    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor(dictionary=True)

        cursor.execute("SELECT * FROM actuador")
        actuadores = cursor.fetchall()

        cursor.close()
        conexion.close()

        return jsonify(actuadores), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener actuadores', 'error': str(e)}), 500

# 4. Ruta para exportar datos entre fechas en formato Excel
@app.route('/exportar', methods=['GET'])
def exportar_datos():
    fecha_inicio = request.args.get('fecha_inicio')
    fecha_fin = request.args.get('fecha_fin')

    try:
        conexion = mysql.connector.connect(**db_config)
        query = """
            SELECT * FROM sensor_datos 
            WHERE fecha >= %s AND fecha <= %s
        """
        df = pd.read_sql(query, conexion, params=[fecha_inicio, fecha_fin])
        conexion.close()

        # Exportar a Excel en memoria
        output = BytesIO()
        writer = pd.ExcelWriter(output, engine='xlsxwriter')
        df.to_excel(writer, index=False, sheet_name='Datos')
        writer.save()
        output.seek(0)

        return send_file(output, download_name='datos.xlsx', as_attachment=True)

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al exportar datos', 'error': str(e)}), 500

# 5. Ruta para traer datos de dispositivos entre fechas específicas
@app.route('/dispositivos/fecha', methods=['GET'])
def obtener_dispositivos_fecha():
    fecha_inicio = request.args.get('fecha_inicio')
    fecha_fin = request.args.get('fecha_fin')

    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor(dictionary=True)

        query = """
            SELECT d.*, sd.* 
            FROM dispositivo d 
            JOIN sensor_datos sd ON d.id_dispositivo = sd.dispositivo_id
            WHERE sd.fecha >= %s AND sd.fecha <= %s
        """
        cursor.execute(query, (fecha_inicio, fecha_fin))
        datos = cursor.fetchall()

        cursor.close()
        conexion.close()

        return jsonify(datos), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener datos por fecha', 'error': str(e)}), 500

# 6. Ruta para traer lecturas de un sensor específico en una fecha específica
@app.route('/lectura_sensor', methods=['GET'])
def obtener_lectura_sensor():
    sensor_id = request.args.get('sensor_id')
    fecha = request.args.get('fecha')

    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor(dictionary=True)

        query = """
            SELECT * FROM sensor_datos 
            WHERE nodo_id = %s AND DATE(fecha) = %s
        """
        cursor.execute(query, (sensor_id, fecha))
        datos = cursor.fetchall()

        cursor.close()
        conexion.close()

        return jsonify(datos), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener lectura del sensor', 'error': str(e)}), 500

# 7. Ruta para ver las lecturas de un solo sensor según su nombre o ID
@app.route('/sensor', methods=['GET'])
def obtener_lecturas_sensor():
    sensor_id = request.args.get('sensor_id')
    nombre_sensor = request.args.get('nombre_sensor')

    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor(dictionary=True)

        if sensor_id:
            query = "SELECT * FROM sensor_datos WHERE nodo_id = %s"
            cursor.execute(query, (sensor_id,))
        elif nombre_sensor:
            query = "SELECT * FROM sensor_datos WHERE nombre_sensor = %s"
            cursor.execute(query, (nombre_sensor,))
        else:
            return jsonify({'status': 'Especifique sensor_id o nombre_sensor'}), 400

        datos = cursor.fetchall()
        cursor.close()
        conexion.close()

        return jsonify(datos), 200

    except Exception as e:
        print(f"Error: {e}")
        return jsonify({'status': 'Error al obtener lecturas del sensor', 'error': str(e)}), 500

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000, debug=True)
