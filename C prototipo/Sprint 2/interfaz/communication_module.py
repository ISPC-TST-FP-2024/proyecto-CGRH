# communication_module.py

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
    def connect(self):
        print("Conectando a través de Bluetooth...")
        # Código específico para conectar BLE

    def send_data(self, data):
        print(f"Enviando datos por Bluetooth: {data}")
        # Código para enviar datos por BLE

    def receive_data(self):
        print("Recibiendo datos por Bluetooth...")
        # Código para recibir datos por BLE
        return {"status": "success", "data": "datos recibidos BLE"}


class WiFiCommunication(CommunicationModule):
    """Clase para la comunicación por Wi-Fi"""
    def connect(self):
        print("Conectando a través de Wi-Fi...")
        # Código específico para conectar Wi-Fi

    def send_data(self, data):
        print(f"Enviando datos por Wi-Fi: {data}")
        # Código para enviar datos por HTTP/REST

    def receive_data(self):
        print("Recibiendo datos por Wi-Fi...")
        # Código para recibir datos por HTTP
        return {"status": "success", "data": "datos recibidos Wi-Fi"}
