#include <DHT.h> // Inclui a biblioteca DHT.h para utilizar as funções do sensor DHT

#define DHTPIN 15 // Define o pino ao qual o sensor DHT está conectado (pino GPIO 15)
#define DHTTYPE DHT11 // Define o tipo de sensor DHT que está sendo usado (DHT11)

DHT dht(DHTPIN, DHTTYPE); // Inicializa o objeto DHT com o pino e tipo definidos acima

void setup() {
  Serial.begin(115200); // Inicializa a comunicação serial com a taxa de transmissão de 115200 bps
  Serial.println(F("DHT11 example!")); // Imprime uma mensagem na porta serial indicando que é um exemplo do DHT11
  dht.begin(); // Inicializa o sensor DHT
}

void loop() {
  float temperature = dht.readTemperature(); // Lê a temperatura do sensor DHT e armazena na variável temperature
  float humidity = dht.readHumidity(); // Lê a umidade do sensor DHT e armazena na variável humidity
  
  // Verifica se os dados lidos do sensor são válidos (não são NaN)
  if (!isnan(temperature) && !isnan(humidity)) {
    print_data(temperature, humidity); // Chama a função para imprimir os dados
  } else {
    Serial.println(F("Failed to read from DHT sensor!")); // Imprime uma mensagem de falha na leitura do sensor
  }

  delay(2000); // Aguarda 2000 milissegundos (2 segundos)
}

// Função para imprimir os dados do sensor DHT na porta serial
void print_data(float temperature, float humidity) {
  Serial.print(F("Humidity: ")); // Imprime a string "Humidity: " na porta serial
  Serial.print(humidity); // Imprime o valor da umidade na porta serial
  Serial.print(F("% Temperature: ")); // Imprime a string "% Temperature: " na porta serial
  Serial.print(temperature); // Imprime o valor da temperatura na porta serial
  Serial.println(F("°C")); // Imprime a string "°C" na porta serial e vai para uma nova linha
}