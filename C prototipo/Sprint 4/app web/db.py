# db.py
import mysql.connector
from config import DB_CONFIG

def get_db_connection():
    """
    Retorna una nueva conexión a la base de datos.
    """
    return mysql.connector.connect(**DB_CONFIG)

def ejecutar_consulta(query, params=()):
    """
    Ejecuta una consulta en la base de datos y retorna los resultados.
    """
    conexion = get_db_connection()
    cursor = conexion.cursor(dictionary=True)
    cursor.execute(query, params)
    resultados = cursor.fetchall()
    cursor.close()
    conexion.close()
    return resultados

def insertar_datos(query, params):
    """
    Inserta datos en la base de datos y confirma la transacción.
    """
    conexion = get_db_connection()
    cursor = conexion.cursor()
    cursor.execute(query, params)
    conexion.commit()
    cursor.close()
    conexion.close()
