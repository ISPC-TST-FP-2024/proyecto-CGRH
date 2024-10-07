from communication_module import BLECommunication, WiFiCommunication

class CommunicationStrategy:
    """Clase que selecciona la estrategia de comunicación"""
    def __init__(self, communication_type):
        if communication_type == 'BLE':
            self.communication = BLECommunication()
        elif communication_type == 'WiFi':
            self.communication = WiFiCommunication()
        else:
            raise ValueError("Tipo de comunicación no soportado")

    def connect(self):
        self.communication.connect()

    def send_data(self, data):
        return self.communication.send_data(data)

    def receive_data(self):
        return self.communication.receive_data()
