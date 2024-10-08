from bleak import BleakClient
import asyncio

# Dirección MAC de tu ESP32
BLE_ADDRESS = "xx:xx:xx:xx:xx:xx"
CHARACTERISTIC_UUID = "87654321-4321-4321-4321-210987654321"

async def connect_and_communicate():
    async with BleakClient(BLE_ADDRESS) as client:
        # Conectar
        print("Conectado al ESP32")

        # Leer datos de la característica
        data = await client.read_gatt_char(CHARACTERISTIC_UUID)
        print(f"Datos recibidos del ESP32: {data.decode('utf-8')}")

        # Enviar datos al ESP32
        data_to_send = "Hola ESP32"
        await client.write_gatt_char(CHARACTERISTIC_UUID, data_to_send.encode('utf-8'))
        print(f"Datos enviados al ESP32: {data_to_send}")

asyncio.run(connect_and_communicate())
