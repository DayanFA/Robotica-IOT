#include <WiFi.h> // Biblioteca para conexão WiFi
#include <PubSubClient.h> // Biblioteca para comunicação MQTT
#include "DHTesp.h" // Biblioteca para sensor DHT

const int DHT_PIN = 15; // Define o pino de conexão do sensor DHT

DHTesp dhtSensor; // Cria um objeto para o sensor DHT

// Credenciais da rede WiFi
const char* ssid = "WIFIESP32";
const char* password = "WIFIESP32";

// Endereço do servidor MQTT
const char* mqtt_server = "10.0.0.103";

WiFiClient espClient; // Cria um objeto WiFiClient
PubSubClient client(espClient); // Cria um cliente MQTT usando o WiFiClient
unsigned long lastMsg = 0; // Armazena o tempo da última mensagem enviada
#define MSG_BUFFER_SIZE  (50) // Define o tamanho do buffer da mensagem
float temp = 0; // Variável para armazenar a temperatura
float hum = 0; // Variável para armazenar a umidade
int value = 0; // Variável para outros valores (não utilizada neste código)

void setup_wifi() {
  delay(10);
  // Inicia a conexão com a rede WiFi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); // Define o modo WiFi como estação
  WiFi.begin(ssid, password); // Inicia a conexão WiFi

  // Aguarda até que a conexão seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros()); // Inicializa o gerador de números aleatórios

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); // Exibe o endereço IP obtido
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Função de callback para receber mensagens MQTT
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Liga ou desliga o LED com base na mensagem recebida
  if ((char)payload[0] == '1') {
    digitalWrite(18, HIGH); // Liga o LED
  } else if((char)payload[0] == '0') {
    digitalWrite(18, LOW); // Desliga o LED
  }
}

void reconnect() {
  // Tenta reconectar ao servidor MQTT
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Cria um ID de cliente aleatório
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Tenta conectar
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      // Publica uma mensagem de anúncio
      client.publish("omar123/mqtt", "iotfrontier");
      // Reinscreve no tópico
      client.subscribe("omar123/mqtt");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Espera 5 segundos antes de tentar novamente
      delay(5000);
    }
  }
}

void setup() {
  pinMode(18, OUTPUT); // Inicializa o pino do LED como saída
  Serial.begin(115200); // Inicializa a comunicação serial
  setup_wifi(); // Conecta ao WiFi
  client.setServer(mqtt_server, 1883); // Define o servidor MQTT e a porta
  client.setCallback(callback); // Define a função de callback para o cliente MQTT
  dhtSensor.setup(DHT_PIN, DHTesp::DHT11); // Inicializa o sensor DHT
  analogRead(2); // Realiza uma leitura analógica no pino 2 (não utilizado neste código)
}

void loop() {
  if (!client.connected()) {
    reconnect(); // Reconnecta ao servidor MQTT se necessário
  }
  client.loop(); // Mantém a comunicação MQTT

  unsigned long now = millis(); // Obtém o tempo atual
  if (now - lastMsg > 2000) { // Verifica se 2 segundos se passaram desde a última mensagem
    lastMsg = now; // Atualiza o tempo da última mensagem
    TempAndHumidity data = dhtSensor.getTempAndHumidity(); // Obtém os dados de temperatura e umidade

    String temp = String(data.temperature, 2); // Converte a temperatura para string
    Serial.print("Temperature: ");
    Serial.println(temp);
    client.publish("omar123/temperature", temp.c_str()); // Publica a temperatura no tópico MQTT
    
    String hum = String(data.humidity, 1); // Converte a umidade para string
    Serial.print("Humidity: ");
    Serial.println(hum);
    client.publish("omar123/humidity", hum.c_str()); // Publica a umidade no tópico MQTT
  }
}