from strategy import CommunicationStrategy
import asyncio

async def main():
    communication_type = "BLE"  # Puedes cambiar entre "BLE" y "WiFi"
    communication_module = CommunicationStrategy(communication_type)

    # Conectar al módulo de comunicación seleccionado
    await communication_module.connect()

    # Enviar datos
    data_to_send = {"sensor": "temperatura", "valor": 25.5}
    await communication_module.send_data(data_to_send)

    # Recibir datos
    data_received = await communication_module.receive_data()
    print(f"Datos recibidos: {data_received}")

if __name__ == "__main__":
    asyncio.run(main())
