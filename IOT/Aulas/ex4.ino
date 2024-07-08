//DIRETIVAS
#define b1 4
#define b2 16
#define pinLed 13

//Variaveis
bool ledState = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(pinLed, OUTPUT);
  digitalWrite(pinLed, ledState);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(b1));
  //Serial.println(digitalRead(b2));

  if(!digitalRead(b1)){
    while(!digitalRead(b1)){
      delay(25);
    }
    ledState = !ledState;
    digitalWrite(pinLed, ledState);
  }

  if(!digitalRead(b2)){
    while(!digitalRead(b2)){
      delay(25);
    }
    ledState = !ledState;
    digitalWrite(pinLed, ledState);
  }
}
