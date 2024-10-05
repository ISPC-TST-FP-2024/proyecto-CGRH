# main.py

from strategy import CommunicationStrategy

def main():
    communication_type = "WiFi"  # Aquí puedes cambiar a "BLE" según sea necesario
    communication_module = CommunicationStrategy(communication_type)

    # Conectar al módulo de comunicación seleccionado
    communication_module.connect()

    # Enviar datos
    data_to_send = {"sensor": "temperatura", "valor": 25.5}
    communication_module.send_data(data_to_send)

    # Recibir datos
    data_received = communication_module.receive_data()
    print(f"Datos recibidos: {data_received}")

if __name__ == "__main__":
    main()
