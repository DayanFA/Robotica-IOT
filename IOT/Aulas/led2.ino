#include <Adafruit_GFX.h>        // Inclui a biblioteca Adafruit GFX para gráficos
#include <Adafruit_NeoMatrix.h>  // Inclui a biblioteca Adafruit NeoMatrix para matriz de LEDs
#include <Adafruit_NeoPixel.h>   // Inclui a biblioteca Adafruit NeoPixel para controle dos LEDs

#define PIN 17                   // Pino de controle dos LEDs

// Inicializa a matriz NeoPixel com as seguintes configurações:
// - 4 linhas e 8 colunas
// - Orientação do texto: de cima para baixo e da direita para a esquerda, estilo colunas progressivas
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(4, 8, PIN,
  NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB + NEO_KHZ800);

// Define um array de cores para usar na matriz
const uint16_t colors[] = {
  matrix.Color(255, 0, 0),   // Vermelho
  matrix.Color(0, 255, 0),   // Verde
  matrix.Color(0, 0, 255)    // Azul
};

void setup() {
  matrix.begin();               // Inicializa a matriz NeoPixel
  matrix.setTextWrap(false);    // Desabilita a quebra automática de texto
  matrix.setBrightness(20);     // Define o brilho dos LEDs (0-255)
  matrix.setTextColor(colors[0]); // Define a cor inicial do texto
}

int x = matrix.width();  // Inicializa a posição horizontal da letra "A" fora da tela
int pass = 0;            // Variável para alternar entre as cores

void loop() {
  matrix.fillScreen(0);  // Limpa a tela da matriz (define todos os LEDs como desligados)
  
  // Escreve a letra "A" na matriz na posição (x, 0) com a cor atual
  matrix.drawChar(x, 0, 'A', colors[pass], 0, 1);

  if (++x >= matrix.width()) {       // Move a letra "A" para a esquerda e reinicia quando ultrapassar uma certa posição
      // Define a posição horizontal de volta para o lado direito da matriz
    x=-10;
    // Alterna entre as cores do array colors[] para cada reinício da letra "A"
    if (++pass >= 3) pass = 0;  // Se pass for maior ou igual a 3, redefine pass para 0
    matrix.setTextColor(colors[pass]); // Define a próxima cor para o texto
  }
  
  matrix.show();         // Exibe a matriz com as alterações feitas
  delay(200);            // Aguarda 200 milissegundos antes de repetir o loop
}