from bleak import BleakClient
from exceptions import BLEConnectionError, WiFiConnectionError

# Dirección MAC del ESP32 (cámbiala a la correcta)
BLE_ADDRESS = "xx:xx:xx:xx:xx:xx"
CHARACTERISTIC_UUID = "87654321-4321-4321-4321-210987654321"

class CommunicationError(Exception):
    """Excepción general para errores de comunicación"""
    pass

class CommunicationModule:
    """Clase base para la interfaz de comunicación"""
    def connect(self):
        raise NotImplementedError("Debe implementar el método 'connect' en una subclase")

    def send_data(self, data):
        raise NotImplementedError("Debe implementar el método 'send_data' en una subclase")

    def receive_data(self):
        raise NotImplementedError("Debe implementar el método 'receive_data' en una subclase")


class BLECommunication(CommunicationModule):
    """Clase para la comunicación por Bluetooth"""
    def __init__(self):
        self.client = BleakClient(BLE_ADDRESS)

    async def connect(self):
        try:
            await self.client.connect()
            print("Conectado a través de Bluetooth")
        except Exception as e:
            raise BLEConnectionError(f"Error de conexión BLE: {e}")

    async def send_data(self, data):
        # Convertir datos a bytes antes de enviarlos
        data_bytes = bytes(str(data), 'utf-8')
        await self.client.write_gatt_char(CHARACTERISTIC_UUID, data_bytes)
        print(f"Enviando datos por Bluetooth: {data}")

    async def receive_data(self):
        data = await self.client.read_gatt_char(CHARACTERISTIC_UUID)
        print("Recibiendo datos por Bluetooth...")
        return data.decode('utf-8')


class WiFiCommunication(CommunicationModule):
    """Clase para la comunicación por Wi-Fi"""
    def connect(self):
        print("Conectando a través de Wi-Fi...")
        # Código para conectar Wi-Fi (omitir en este caso)

    def send_data(self, data):
        print(f"Enviando datos por Wi-Fi: {data}")
        # Código para enviar datos por HTTP/REST (omitir en este caso)

    def receive_data(self):
        print("Recibiendo datos por Wi-Fi...")
        return {"status": "success", "data": "datos recibidos Wi-Fi"}
