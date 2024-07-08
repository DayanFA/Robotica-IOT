//include referente a display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// declaracao das variaveis a serem usadas
#define ldr 36
int valor_ldr;
int touch;
int touch2;

//declarações para o display
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(); //INICIALIZA A BIBLIOTECA WIRE
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(ldr, OUTPUT);
  
  //Inicializa display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1); // Fonte do texto
  display.setTextColor(WHITE); // Cor do texto
  display.setCursor(64, 10);  // Posiciona o cursor
  display.println("ola "); // Imprime mensagem
  display.display(); 
  display.clearDisplay(); //limpa display
  display.setTextSize(2); // Fonte do texto
  delay(5000);

}

void loop() {
  // leitura do LDR
  valor_ldr = analogRead(ldr);

  // escrita no display
  display.clearDisplay(); //limpa display
  delay(100);
  display.setCursor(0, 5);  // Posiciona o cursor
  display.println(valor_ldr); // Imprime valor
  display.display(); 

  // leitura do sensor capacitivo
  touch=touchRead(33);
  touch2=touchRead(27);

    if(touch<25){
      display.setCursor(0, 36);
      display.println("OLA IAN"); // Imprime valor
      display.display(); 
    
    }
    if(touch2<25){
      display.setCursor(0, 36);
      display.println("bom dia"); // Imprime valor
      display.display(); 
    
    
    }
}