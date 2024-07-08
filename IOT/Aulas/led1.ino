#include <Adafruit_GFX.h>        // Inclui a biblioteca Adafruit GFX para gráficos
#include <Adafruit_NeoMatrix.h>  // Inclui a biblioteca Adafruit NeoMatrix para matriz de LEDs
#include <Adafruit_NeoPixel.h>   // Inclui a biblioteca Adafruit NeoPixel para controle dos LEDs

#define PIN 17                   // Pino de controle dos LEDs

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(4, 8, PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(matrix.Color(255, 0, 0)); // Cor vermelha para a letra "A"
}

void loop() {
  matrix.fillScreen(0);  // Limpa a tela da matriz

  // Desenha a letra "A" na posição (0, 0) com a cor vermelha
  matrix.drawChar(0, 0, 'A', matrix.Color(255, 0, 0), 0, 1);

  matrix.show();         // Exibe a matriz
}