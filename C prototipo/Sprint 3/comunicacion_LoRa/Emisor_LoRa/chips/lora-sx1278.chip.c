// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT
// Copyright 2023 Fernando gimenez

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 64  // Tamaño máximo del mensaje

typedef struct {
  pin_t cs_pin;         // Pin de Chip Select (CS)
  uint32_t spi;         // Bus SPI
  uint8_t spi_buffer[1];  // Buffer para un byte por vez
  char mensaje[MAX_BUFFER_SIZE];  // Almacena el mensaje recibido
  int mensaje_index;    // Índice para la recepción del mensaje
} chip_state_t;

static void chip_pin_change(void *user_data, pin_t pin, uint32_t value);
static void chip_spi_done(void *user_data, uint8_t *buffer, uint32_t count);

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  
  chip->cs_pin = pin_init("CS", INPUT_PULLUP);
  chip->mensaje_index = 0;  // Inicializa el índice del mensaje

  const pin_watch_config_t watch_config = {
    .edge = BOTH,
    .pin_change = chip_pin_change,
    .user_data = chip,
  };
  pin_watch(chip->cs_pin, &watch_config);

  const spi_config_t spi_config = {
    .sck = pin_init("SCK", INPUT),
    .miso = pin_init("MISO", INPUT),
    .mosi = pin_init("MOSI", INPUT),
    .done = chip_spi_done,
    .user_data = chip,
  };
  chip->spi = spi_init(&spi_config);
  
  printf("Custom LoRa SPI Chip iniciado!\n");
}

// Manejador de cambios en el pin CS
void chip_pin_change(void *user_data, pin_t pin, uint32_t value) {
  chip_state_t *chip = (chip_state_t*)user_data;
  
  if (pin == chip->cs_pin) {
    if (value == LOW) {  // Selección del chip (CS activado)
      printf("SPI chip seleccionado\n");
      chip->mensaje_index = 0;  // Reinicia el índice del mensaje
      chip->spi_buffer[0] = ' ';  // Enviar byte inicial dummy
      spi_start(chip->spi, chip->spi_buffer, sizeof(chip->spi_buffer));
    } else {  // CS desactivado (transacción SPI finalizada)
      printf("SPI chip deseleccionado\n");
      spi_stop(chip->spi);
    }
  }
}

// Manejador al completar una transferencia SPI
void chip_spi_done(void *user_data, uint8_t *buffer, uint32_t count) {
  chip_state_t *chip = (chip_state_t*)user_data;

  if (!count) {
    return;  // Si no hay datos, salir
  }

  // Agrega el byte recibido al mensaje
  chip->mensaje[chip->mensaje_index++] = buffer[0];
  
  // Si se recibe el carácter '\n', el mensaje está completo
  if (buffer[0] == '\n' || chip->mensaje_index >= MAX_BUFFER_SIZE - 1) {
    chip->mensaje[chip->mensaje_index] = '\0';  // Termina el string
    printf("Mensaje recibido: %s\n", chip->mensaje);

    // Responder con "ACK\n" por SPI
    const char *ack = "ACK\n";
    for (int i = 0; i < strlen(ack); i++) {
      chip->spi_buffer[0] = ack[i];
      spi_start(chip->spi, chip->spi_buffer, sizeof(chip->spi_buffer));
    }
  } else {
    // Continuar leyendo el siguiente byte si CS sigue activo
    if (pin_read(chip->cs_pin) == LOW) {
      spi_start(chip->spi, chip->spi_buffer, sizeof(chip->spi_buffer));
    }
  }
}