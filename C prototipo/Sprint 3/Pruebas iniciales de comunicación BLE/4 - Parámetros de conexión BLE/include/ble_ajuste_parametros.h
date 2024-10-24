#ifndef BLE_AJUSTE_PARAMETROS_H
#define BLE_AJUSTE_PARAMETROS_H

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

class BLE_AjusteParametros; // Declaración anticipada

class MyServerCallbacks : public BLEServerCallbacks {
public:
    MyServerCallbacks(BLE_AjusteParametros* instance) : instance(instance) {}

    void onConnect(BLEServer* server) override;
    void onDisconnect(BLEServer* server) override;

private:
    BLE_AjusteParametros* instance;
};

class BLE_AjusteParametros {
private:
    BLEServer* servidorBLE;
    BLECharacteristic* caracteristicaBLE;
    bool dispositivoConectado; // Mantener como privado

public:
    BLE_AjusteParametros();
    void iniciarBLE();
    void notificarClientes(const std::string& mensaje);
    void verificarConexion();
    void ajustarParametrosPublicidad(uint32_t intervalo);
    void ajustarParametrosConexion(uint16_t intervaloMinimo, uint16_t intervaloMaximo, uint16_t latencia, uint16_t tiempoEspera);
    
    // Método público para verificar conexión
    bool isDispositivoConectado() const { return dispositivoConectado; }
    void setDispositivoConectado(bool estado) { dispositivoConectado = estado; } // Setter para modificar el estado
};

#endif
