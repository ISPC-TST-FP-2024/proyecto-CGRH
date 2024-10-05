class CommunicationStrategy:
    def __init__(self, communication_type):
        if communication_type == 'BLE':
            self.communication = BLECommunication()
        elif communication_type == 'WiFi':
            self.communication = WiFiCommunication()
        else:
            raise ValueError("Communication type not supported")

    def send_data(self, data):
        self.communication.send_data(data)

    def receive_data(self):
        return self.communication.receive_data()
