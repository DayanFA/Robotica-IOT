#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#define PIN 17
#define NUMPIXELS 32
#define DELAYVAL 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int trigPin = 14;  // Pino de trigger do sensor
const int echoPin = 12;  // Pino de eco do sensor
int distLed;

void setup() {
  pixels.begin();
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
  distLed= round(distance);
  if(distLed<32){
    pixels.clear();
    distLed= distLed-1;
    for(int i=0; i<distLed; i++){
    pixels.setPixelColor(i, pixels.Color(0,0,50));
    pixels.show();
    delay(DELAYVAL);
}
}
  delay(500);  // Aguarda 1 segundo antes da próxima leitura

  

}