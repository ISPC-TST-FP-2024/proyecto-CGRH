class CommunicationError(Exception):
    """Excepción genérica para problemas de comunicación"""
    pass

class BLEConnectionError(CommunicationError):
    """Excepción específica para errores de conexión BLE"""
    pass

class WiFiConnectionError(CommunicationError):
    """Excepción específica para errores de conexión Wi-Fi"""
    pass
