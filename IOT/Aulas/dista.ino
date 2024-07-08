#include <Arduino.h>

const int trigPin = 14;  // Pino de trigger do sensor
const int echoPin = 12;  // Pino de eco do sensor

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  long duration, distance;
  
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
  
  // Mostra a distância no Monitor Serial
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(1000);  // Aguarda 1 segundo antes da próxima leitura
}