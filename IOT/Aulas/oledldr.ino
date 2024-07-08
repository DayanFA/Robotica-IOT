// include referente a display
#include <Wire.h> // biblioteca que permite você se comunicar com dispositivos I2C
#include <Adafruit_GFX.h> // biblioteca gráfica principal para todos os monitores da adafruit
#include <Adafruit_SSD1306.h> // biblioteca para os OLEDs da adafruit monocromáticos baseados em drivers SSD1306

// declaração das variaveis a serem usadas
#define ldr 36 // pino da placa que está conectado ao LDR
int valor_ldr; // variavel que guarda o valor do LDR
int touch; // Declara a variável touch como inteiro
int touch2; // Declara a variável touch2 como inteiro

// declarações para o display
#define SCREEN_WIDTH 128 // Largura da tela OLED, em pixels
#define SCREEN_HEIGHT 64 // Altura da tela OLED, em pixels
// Declaração para um monitor SSD1306 conectado a pinos I2C (SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Função para inicializar o display
void initializeDisplay() {
  Wire.begin(); // INICIALIZA A BIBLIOTECA WIRE
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed")); // Significa que não deu certo a comunicação com o OLED
    for (;;);
  }
  delay(1000);

  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(35, 30); // Posiciona o cursor
  display.println("inicializando"); // Imprime mensagem
  display.display();
  display.clearDisplay(); // limpa display
  display.setTextSize(2); // Fonte do texto
  delay(3000);
}

// Função para ler o LDR e atualizar o display
void readAndPrintLDRValue() {
  valor_ldr = analogRead(ldr); // leitura do LDR

  // escrita no display
  display.clearDisplay(); // limpa display
  delay(300);
  display.setCursor(32, 5); // Posiciona o cursor
  display.println(valor_ldr); // Imprime valor
  display.display();
}

// Função para ler o sensor touch e atualizar o display
void readAndPrintTouchValue() {
  // leitura do sensor touch
  touch = touchRead(33);
  touch2 = touchRead(27);

  if (touch < 25) {
    display.setCursor(0, 36);
    display.println("faz o L"); // Imprime valor
    display.display();
    delay(300);
  }
  if (touch2 < 25) {
    display.setCursor(0, 36);
    display.println("ruuuuuuum"); // Imprime valor
    display.display();
    delay(300);
  }
}

void setup() {
  Serial.begin(9600); // Inicialização da comunicação serial, com taxa de transferência em bits por segundo de 9600
  initializeDisplay(); // Inicializa o display
  pinMode(ldr, INPUT); // Define o pino do LDR como entrada
}

void loop() {
  readAndPrintLDRValue(); // Chama a função para ler e imprimir o valor do LDR no display
  readAndPrintTouchValue(); // Chama a função para ler e imprimir o valor do sensor touch no display
}