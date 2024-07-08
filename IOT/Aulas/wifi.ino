#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include "Wire.h" 				// Biblioteca para enviar e receber dados TWI/I2C
#include "Adafruit_GFX.h" 			// Biblioteca para processamento gráfica
#include "Adafruit_SSD1306.h" 		// Biblioteca do controlador SSD1306 (128x64 e 128x32)
Adafruit_SSD1306 display = Adafruit_SSD1306(); 	// Cria objeto Adafruit_SSD1306
#define LDR 36
const int DHT_PIN = 15;

DHTesp dhtSensor;

const char* ssid = "Omar";
const char* password = "12345678";
const char* mqtt_server = "192.168.100.51";
//const char* mqtt_server = "10.0.0.102";
//const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
float temp = 0;
float hum = 0;
int value = 0;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Converte o payload para uma string
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0'; // Adiciona o terminador nulo

  // Visualiza na LCD
  display.setCursor(0, 0); 						// Posição do cursor na tela
  display.clearDisplay();						// Limpa display
  display.print("Sistema"); 						// Escreve texto no display   
  display.setCursor(10, 8); 						// Posição do cursor na tela
  display.print("receb:"); 						// Escreve texto no display
  display.setCursor(55, 8); 						// Posição do cursor na tela
  display.print(message); 						// Escreve texto no display
  display.display(); 							// Mostra texto no display
  delay(1500); 									// Aguarda intervalo de 1,5 segundos

  // Switch on the LED if an 1 was received as first character
  if (message[0] == '1') {
    digitalWrite(18, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else if (message[0] == '0') {
    digitalWrite(18, LOW);  // Turn the LED off by making the voltage HIGH
  }
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      // Once connected, publish an announcement...
      client.publish("omar123/mqtt", "iotfrontier");
      // ... and resubscribe
      client.subscribe("omar123/mqtt");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(18, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11);
  pinMode(LDR,INPUT);
  analogRead(2);
   Wire.begin(); 								// Inicializa biblioteca sensor I2c
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 	// Inicializa dysplay com endereço I2C 0x3C
  display.setTextColor(WHITE); 					// Define cor do texto
  display.setTextSize(1); 						// Define tamanho da fonte do texto
  display.clearDisplay(); 						// Limpa as informações do display
}

void loop() {
 float valorLdr;
 valorLdr=analogRead(LDR);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    TempAndHumidity  data = dhtSensor.getTempAndHumidity();

    String temp = String(data.temperature, 2);
    Serial.print("Temperature: ");
    Serial.println(temp);
    client.publish("omar123/temperature", temp.c_str());
    
    String hum = String(data.humidity, 1);
    Serial.print("Humidity: ");
    Serial.println(hum);
    client.publish("omar123/humidity", hum.c_str());
    //publicando valor de ldr
    String lum = String(valorLdr, 1);
    Serial.print("valor luninosidade: ");
    Serial.println(lum);
    client.publish("omar123/luninosidade", lum.c_str());
  }
}