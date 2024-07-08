/* 
Programa: Informa temperatura, umidade e luminosidade com sensor DHT11 e LDR 
Data: 09/05/2024
*/

#include "Wire.h" 				// Biblioteca para enviar e receber dados TWI/I2C
#include "Adafruit_GFX.h" 			// Biblioteca para processamento gráfica
#include "Adafruit_SSD1306.h" 		// Biblioteca do controlador SSD1306 (128x64 e 128x32)
#include "DHT.h"				// Biblioteca sensor DHT11

// Variáveis de luminosidade, temperatura, etc. 
float luminosidade = 0;                        
float temperatura = 0;                          
float DHT11_temperatura = 0;
float DHT11_umidade = 0;

int PINO_DTH11 = 15; //GPIO conectato ao DHT11
int PINO_LDR = 36;  	//GPIO conectado ao conversor Analodigo digital e LDR
 
Adafruit_SSD1306 display = Adafruit_SSD1306(); 	// Cria objeto Adafruit_SSD1306
DHT dht(PINO_DTH11, DHT11);   				// Cria objeto para sensor DHT11T

void setup() {

  pinMode(PINO_DTH11, INPUT);    				// Define pino do Sensor DHT11
  pinMode(PINO_LDR, INPUT);  					// Define pino do Sensor LDR

  dht.begin(); 								// Inicializa biblioteca WIRE
  Wire.begin(); 								// Inicializa biblioteca sensor I2c

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 	// Inicializa dysplay com endereço I2C 0x3C
  display.setTextColor(WHITE); 					// Define cor do texto
  display.setTextSize(1); 						// Define tamanho da fonte do texto
  display.clearDisplay(); 						// Limpa as informações do display

}

void loop() {

  display.setCursor(0,0); 						// Posição do cursor na tela
  display.clearDisplay();						// Limpa display
  display.print("Sistema"); 						// Escreve texto no display 
  
  // --- lê sensor DHT11 - temperatura e umidade ---    
  DHT11_temperatura  = dht.readTemperature();  
  DHT11_umidade      = dht.readHumidity();  
  
  display.setCursor(10,8); 						// Posição do cursor na tela
  display.print("Temp.:"); 						// Escreve texto no display
  display.setCursor(55,8); 						// Posição do cursor na tela
  display.print(DHT11_temperatura); 				// Escreve texto no display

  display.setCursor(10,16); 					// Posição do cursor na tela
  display.print("Umid: "); 						// Escreve texto no display
  display.setCursor(55,16); 					// Posição do cursor na tela
  display.print(DHT11_umidade); 				// Escreve texto no display

  // --- lê sensor LDR - Luminosidade ---  
  luminosidade = map(analogRead(PINO_LDR), 0, 1023, 255, 0); 

  display.setCursor(10,24); 					// Posição do cursor na tela
  display.print("Lumis: "); 						// Escreve texto no display
  display.setCursor(55,24); 					// Posição do cursor na tela
  display.print(luminosidade); 					// Escreve texto no display

  display.display(); 							// Mostra texto no display
  delay(1500); 								// Aguarda intervalo de 1,5 segundos 

}