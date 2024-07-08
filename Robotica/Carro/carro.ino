#include <AFMotor.h>
 
AF_DCMotor motor(3); //Seleciona o motor 1
AF_DCMotor motor2(4); //Seleciona o motor 1
// Define os pinos do sensor ultrassônico
#define TRIGGER_PIN 9
#define ECHO_PIN 10


void setup()
{
  // Define os pinos do sensor ultrassônico
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
 
  // Inicializa a comunicação serial
  Serial.begin(9600);
}
 
void loop()
{
  // Envia um pulso ultrassônico
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);


  // Mede o tempo que o pulso leva para retornar
  long duration = pulseIn(ECHO_PIN, HIGH);


  // Calcula a distância em centímetros
  int distance = duration * 0.034 / 2;


  // Imprime a distância medida no monitor serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");
  if(distance >0 && distance <10){


    Serial.println("Objeto detectado. Motor parado.");
    motor.setSpeed(0); //Define velocidade baixa
    motor2.setSpeed(0); //Define velocidade baixa
    delay(100);
    motor.setSpeed(255);
    motor2.setSpeed(255);
    motor.run(BACKWARD); //Gira o motor sentido anti-horario
    motor2.run(BACKWARD); //Gira o motor sentido anti-horario
 
    delay(100);


    motor.run(BACKWARD); //Desliga o motor
    motor2.run(FORWARD); //Desliga o motor
    motor.setSpeed(255);
    motor2.setSpeed(255);


    delay(3000);




  } else {


    motor.setSpeed(255); //Define a velocidade maxima
    motor2.setSpeed(255); //Define a velocidade maxima


    motor.run(FORWARD); //Gira o motor sentido horario
    motor2.run(FORWARD); //Gira o motor sentido horario
 
   
  }
    delay(100);
}

