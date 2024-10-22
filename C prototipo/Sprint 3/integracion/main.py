from flask import Flask, request, jsonify
import mysql.connector
import getpass  # Para solicitar la contraseña
from prettytable import PrettyTable  # Para mostrar los datos en formato de tabla

app = Flask(__name__)

# Configuración de conexión a MySQL (servidor local)
def get_db_config():
    password = getpass.getpass('Introduce la contraseña de MySQL para el usuario root: ')
    return {
        'host': 'localhost',
        'user': 'root',
        'password': password,
        'database': 'proyecto_iot',
        'port': 3306
    }

db_config = get_db_config()

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

        # Verificar si el dispositivo ya existe en la base de datos (nombre y apellido)
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
            dispositivo_id = cursor.lastrowid  # Obtenemos el ID del nuevo dispositivo insertado
        else:
            dispositivo_id = dispositivo[0]  # Obtenemos el ID del dispositivo existente

        # Insertar los datos en la tabla sensor_datos, vinculando con el dispositivo_id
        sql_sensor_datos = """
            INSERT INTO sensor_datos (nodo_id, temperatura, humedad, luz_ambiente, 
                                      humedad_suelo_cap, humedad_suelo_res, nivel_agua, dispositivo_id)
            VALUES (%s, %s, %s, %s, %s, %s, %s, %s)
        """
        datos_sensor = (nodo_id, temperatura, humedad, luz_ambiente, humedad_suelo_cap, humedad_suelo_res, nivel_agua, dispositivo_id)
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

# Función para buscar lecturas por ID de dispositivo o nombre
def buscar_lecturas_por_dispositivo():
    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor()

        criterio = input("Buscar por (1) ID del dispositivo o (2) Nombre de la persona: ")
        if criterio == "1":
            dispositivo_id = input("Introduce el ID del dispositivo: ")
            query = "SELECT * FROM sensor_datos WHERE dispositivo_id = %s"
            mostrar_tabla(cursor, query, (dispositivo_id,))
        elif criterio == "2":
            nombre = input("Introduce el nombre: ")
            apellido = input("Introduce el apellido: ")
            query = """
                SELECT sd.* FROM sensor_datos sd
                JOIN dispositivo d ON sd.dispositivo_id = d.id_dispositivo
                WHERE d.nombre = %s AND d.apellido = %s
            """
            mostrar_tabla(cursor, query, (nombre, apellido))

        cursor.close()
        conexion.close()
    except Exception as e:
        print(f"Error al buscar lecturas: {e}")

# Función para buscar actividad de actuadores por ID o nombre
def buscar_actividad_actuador():
    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor()

        criterio = input("Buscar actividad del actuador por (1) ID del dispositivo o (2) Nombre de la persona: ")
        if criterio == "1":
            dispositivo_id = input("Introduce el ID del dispositivo: ")
            query = "SELECT * FROM actuador WHERE dispositivo_id = %s"
            mostrar_tabla(cursor, query, (dispositivo_id,))
        elif criterio == "2":
            nombre = input("Introduce el nombre: ")
            apellido = input("Introduce el apellido: ")
            query = """
                SELECT a.* FROM actuador a
                JOIN dispositivo d ON a.dispositivo_id = d.id_dispositivo
                WHERE d.nombre = %s AND d.apellido = %s
            """
            mostrar_tabla(cursor, query, (nombre, apellido))

        cursor.close()
        conexion.close()
    except Exception as e:
        print(f"Error al buscar actividad del actuador: {e}")

# Función para mostrar todos los datos
def mostrar_todos_los_datos():
    try:
        conexion = mysql.connector.connect(**db_config)
        cursor = conexion.cursor()

        print("Datos de dispositivos:")
        query_dispositivos = "SELECT * FROM dispositivo"
        mostrar_tabla(cursor, query_dispositivos)

        print("Datos de sensores:")
        query_sensores = "SELECT * FROM sensor_datos"
        mostrar_tabla(cursor, query_sensores)

        print("Datos de actuadores:")
        query_actuadores = "SELECT * FROM actuador"
        mostrar_tabla(cursor, query_actuadores)

        cursor.close()
        conexion.close()
    except Exception as e:
        print(f"Error al mostrar todos los datos: {e}")

# Menú interactivo por consola
def mostrar_menu():
    while True:
        print("\n--- MENÚ ---")
        print("1. Buscar lecturas por dispositivo")
        print("2. Buscar actividad de actuador")
        print("3. Mostrar todos los datos")
        print("4. Salir")

        opcion = input("Elige una opción: ")

        if opcion == "1":
            buscar_lecturas_por_dispositivo()
        elif opcion == "2":
            buscar_actividad_actuador()
        elif opcion == "3":
            mostrar_todos_los_datos()
        elif opcion == "4":
            print("Saliendo...")
            break
        else:
            print("Opción no válida. Intenta nuevamente.")

if __name__ == '__main__':
    # Ejecutar menú por consola
    mostrar_menu()
