//DIRETIVAS
//1-DISPLAY OLED
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define WIDTH 128
#define HEIGHT 64

//1-DHT
#include <DHT.h>
#define pinDHT 15
float u, c, f;

//2-SENSOR ULTRASSOM
#include <Ultrasonic.h>
#define trigPin 14
#define echoPin 12
int distanciaCM, distanciaIN;

//BOTOES
#define BOTAO1 16
#define BOTAO2 4

//1,2,6 - INSTANCIAR OBJETOS (DISPLAY, DHT, ULTRASSOM, MATRIZ)
Adafruit_SSD1306 display(WIDTH, HEIGHT, &Wire, -1);
DHT dht11(pinDHT, DHT11);
Ultrasonic ultrasonic(trigPin, echoPin);

//1ao6 - Variaveis
char tela = 'B';
//A -> DHT11 / B -> ULTRASSOM / C -> LDR / D-> RELE


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); // UART
  pinMode(BOTAO1, INPUT);
  pinMode(BOTAO2, INPUT);
  
  //1-INICIALIZAR DISPLAY
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println(F("DISPLAY NÃO ENCONTRADO!!"));
  }
  display.clearDisplay();

  //1-INICIALIZAR DHT
  dht11.begin();

  //2-ULTRASSOM (NADA)
}

void loop() {
  // put your main code here, to run repeatedly:
  //2-LÓGICA BOTOES SELECIONAR TELA
  if(!digitalRead(BOTAO1)){
    while(!digitalRead(BOTAO1)){
      delay(15);
    }
    tela = 'A';
  }

  if(!digitalRead(BOTAO2)){
    while(!digitalRead(BOTAO2)){
      delay(15);
    }
    tela = 'B';
  }

  //1-TELA SENSOR DHT
  if(tela == 'A'){
    //EXIBIR ESTAS INFORMACOES NO DISPLAY
    u = dht11.readHumidity();
    c = dht11.readTemperature();

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,10);
    display.print("UR: ");
    display.print(u);
    display.println(" %.");
    display.setCursor(0, 30);
    display.print("Temp: ");
    display.print(c);
    display.print(" C.");
    display.display();
  }
  //2-TELA SENSOR ULTRASSOM
  if(tela == 'B'){
    distanciaCM = ultrasonic.read();
    distanciaIN = ultrasonic.read(INC);

    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setTextSize(1);
    display.setCursor(0, 10);
    display.print("D: ");
    display.print(distanciaCM);
    display.println(" cm.");
    display.setCursor(0, 30);
    display.print("D: ");
    display.print(distanciaIN);
    display.println(" in.");
    display.display();
  }
  //3-TELA SENSOR LDR
  //4-TELA ESTADO RELE
}