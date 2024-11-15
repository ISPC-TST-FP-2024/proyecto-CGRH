import psycopg2
from psycopg2 import sql, OperationalError
from config import DB_CONFIG

def get_db_connection():
    """
    Returns a new connection to the PostgreSQL database.
    """
    try:
        connection = psycopg2.connect(
            host=DB_CONFIG['host'],
            port=DB_CONFIG['port'],
            user=DB_CONFIG['user'],
            password=DB_CONFIG['password'],
            database=DB_CONFIG['database']
        )
        return connection
    except OperationalError as e:
        print(f"Error connecting to the database: {e}")
        return None

def ejecutar_consulta(query, params=()):
    """
    Executes a query in the database and returns the results.
    """
    try:
        with get_db_connection() as conexion:
            with conexion.cursor() as cursor:
                cursor.execute(query, params)
                resultados = cursor.fetchall()
                return resultados
    except Exception as e:
        print(f"Error executing query: {e}")
        return None

def insertar_datos(query, params):
    """
    Inserts data into the database and commits the transaction.
    """
    try:
        with get_db_connection() as conexion:
            with conexion.cursor() as cursor:
                cursor.execute(query, params)
                conexion.commit()
    except Exception as e:
        print(f"Error inserting data: {e}")
