#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

char* ssid = "Test";
const char* password = "12345678";
const char* serverName = "[ip]";

const int trigPin = 14; // Pino de trigger do sensor
const int echoPin = 12; // Pino de eco do sensor
#define pinDHT 15 // Pino do sensor DHT
#define soilMoisturePin 39 // Pino do sensor de umidade do solo

DHT dht11(pinDHT, DHT11); // Inicializa o sensor DHT

const float riverHeight = 205.0; // Altura do rio em centímetros

void setup() {
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(soilMoisturePin, INPUT);

    // Inicializa o sensor DHT
    dht11.begin();

    // Conecta ao WiFi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi");
    analogRead(2);
}

void loop() {
    long duration;
    float distance, waterLevel;
    // Envia um pulso no pino de trigger
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Lê o tempo de eco do pino de echo
    duration = pulseIn(echoPin, HIGH);
    // Calcula a distância em centímetros
    distance = duration * 0.034 / 2;
    // Calcula o nível da água
    waterLevel = riverHeight - distance;

    // Lê os dados do sensor DHT
    float humidity = dht11.readHumidity();
    float temperature = dht11.readTemperature();

    // Lê os dados do sensor de umidade do solo
    int soilMoisture = analogRead(soilMoisturePin);

    // Mostra os dados dos sensores no Monitor Serial
    Serial.print("Nível da água: ");
    Serial.print(waterLevel);
    Serial.println(" cm");
    Serial.print("Umidade: ");
    Serial.print(humidity);
    Serial.println(" %");
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Umidade do solo: ");
    Serial.println(soilMoisture);

    if ((WiFi.status() == WL_CONNECTED)) { //Verifica a conexão Wi-Fi
        HTTPClient http;

        // Inicia a conexão e envia o tipo de cabeçalho HTTP
        http.begin(serverName);

        // Adiciona os dados dos sensores ao corpo da solicitação
        String httpRequestData = "water_level_data=" + String(waterLevel) + "&humidity=" + String(humidity) + "&temperature=" + String(temperature) + "&soil_moisture=" + String(soilMoisture);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = http.POST(httpRequestData);

        http.end();

        // Se o nível da água ultrapassar um certo valor, envia uma mensagem para o WhatsApp
        if (waterLevel > 100) {
            String callMeBotUrl = "https://api.callmebot.com/whatsapp.php?phone=55&text=ALERTA%20DE%20EMERGÊNCIA:%20O%20nível%20da%20água%20está%20muito%20alto.%20Evacue%20imediatamente!&apikey=123";
            http.begin(callMeBotUrl);
            httpResponseCode = http.GET();
            http.end();
        }
    }
    else {
        Serial.println("Erro na conexão WiFi");
    }

    delay(1000);
}