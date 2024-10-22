/*************
Por algun motivo no consigo que se despligue la pantalla a pesar de utilizar las librerias necesarias
A modo de ejemlplo dejo el sguiente proyecto de wokwi, que si lo consigue.

https://wokwi.com/projects/393764285173336065

El codigo utilizado igualmente, es para la ejecucion y procesos de la ST7735S
Origial y distinto del proyecto previamente mostrado

************** */

/**********
Como no se pueden observar los pines. Esta es la disposicion

VCC (Pantalla) → 3.3V
GND (Pantalla) → GND 
SCL (Pantalla) → Pin 18 (SCK)
SDA (Pantalla) → Pin 23 (MOSI)
RES (Pantalla) → Pin 4 
DC (Pantalla) → Pin 2 
CS (Pantalla) → Pin 5 

***********/

#include <Adafruit_GFX.h>      // Librería gráfica
#include <Adafruit_ST7735.h>   // Librería para la pantalla ST7735
#include <SPI.h>               // Comunicación SPI

// Definir pines para la pantalla ST7735
#define TFT_CS     5    // Chip select
#define TFT_RST    4    // Reset
#define TFT_DC     2    // Data/Command

// Inicializar pantalla ST7735 (160x128)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Inicializar comunicación serial
  Serial.begin(115200);

  // Inicializar la pantalla
  tft.initR(INITR_BLACKTAB);  // Inicializar con el tipo de pantalla
  tft.fillScreen(ST77XX_BLACK);  // Fondo negro

  // Mostrar un texto en la pantalla a reemplazar por lo elegido luego en el proyecto
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 10);
  tft.println("hola");

}

void loop() {
  // Alternar el color del fondo cada segundo
  tft.fillScreen(ST77XX_BLUE);
  delay(1000);
  tft.fillScreen(ST77XX_GREEN);
  delay(1000);
}
