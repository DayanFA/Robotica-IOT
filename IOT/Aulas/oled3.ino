#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
#define ldr 36


int valor_ldr;
const uint16_t RECV_PIN = 23; 

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


IRrecv irrecv(RECV_PIN);
decode_results results;


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
  display.setCursor(1, 30); // Posiciona o cursor
  display.println("inicializando"); // Imprime mensagem
  display.display();
  display.clearDisplay(); // limpa display
  display.setTextSize(2); // Fonte do texto
  delay(3000);
}


void setup()
{
  Serial.begin(115200);
   initializeDisplay();
  irrecv.enableIRIn();
}

void loop()
{
  if(irrecv.decode(&results))
  {

    

    // escrita no display
    display.clearDisplay(); // limpa display
    delay(300);
    display.setCursor(1, 5); // Posiciona o cursor
    display.println(results.value, HEX); // Imprime valor
    display.display();

    irrecv.resume();
    delay(10);
  }
}