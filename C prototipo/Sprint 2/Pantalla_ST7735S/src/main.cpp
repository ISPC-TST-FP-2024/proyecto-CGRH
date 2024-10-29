#include <Adafruit_GFX.h>      // Librería gráfica
#include <Adafruit_ST7735.h>   // Librería para la pantalla ST7735
#include <SPI.h>               // Comunicación SPI
#include "Teclado.h"           // Incluir la librería del teclado
#include "Menu.h"              // Incluir la librería del menú

// Definir pines para la pantalla ST7735
#define TFT_CS     5    // Chip select
#define TFT_RST    4    // Reset
#define TFT_DC     2    // Data/Command

// Inicializar pantalla ST7735 (160x128)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Teclado teclado(9, 8, 7, 6, 3, 2, 1, 0); // Ajusta los pines según tu conexión
Menu menu(tft, teclado); // Asegúrate de que Menu acepte el tipo correcto

void setup() {
  // Inicializar comunicación serial
  Serial.begin(115200);
  Serial.println("Iniciando pantalla...");

  // Inicializar la pantalla
  tft.initR(INITR_BLACKTAB);  // Inicializar con el tipo de pantalla
  Serial.println("Pantalla inicializada.");
  tft.fillScreen(ST77XX_BLACK);  // Fondo negro

  // Inicializar teclado
  teclado.iniciar();

  // Mostrar un texto inicial
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("Hola");

  // Mostrar menú
  menu.displayMenu();
}

void loop() {
  // Lógica de navegación del menú
  menu.navigate();
  
  // Alternar el color del fondo cada segundo (opcional)
  // tft.fillScreen(ST77XX_BLUE);
  // delay(1000);
  // tft.fillScreen(ST77XX_GREEN);
  // delay(1000);
}
