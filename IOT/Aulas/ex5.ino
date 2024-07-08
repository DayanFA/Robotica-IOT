//DIRETIVAS
#define pirPin 39
#define ledPin 13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println(digitalRead(pirPin));
  
  if(digitalRead(pirPin)){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
  
}
