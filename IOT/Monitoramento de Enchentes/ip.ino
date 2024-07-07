#include <WiFi.h>

const char* ssid = "Test";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);

  // Conecta ao WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Imprime o endereço IP local
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {}