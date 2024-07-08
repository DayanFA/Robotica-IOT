//DIRETIVAS
#define pinRelay 2
#define pirPin 39
#define b1 4

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pinRelay, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(b1, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(pinRelay, HIGH);
  //delay(1000); // this speeds up the simulation

  if(digitalRead(pirPin) || !digitalRead(b1)){
    digitalWrite(pinRelay, HIGH);
  }else{
    digitalWrite(pinRelay, LOW);
  }
}
