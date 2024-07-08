// C++ code
//
#define ledVERM 11
int ledVERDE = 7;
int ledAMAR = 3;


void setup()
{
  pinMode(ledVERM, OUTPUT);
  pinMode(ledVERDE, OUTPUT);
  pinMode(ledAMAR, OUTPUT);
  Serial.begin(115200);
  
}

void loop()
{
	/*
  	digitalWrite(ledVERM, HIGH);
  	delay(1000);
  	digitalWrite(ledVERM, LOW);
  	digitalWrite(ledVERDE, HIGH);
  	delay(2000);
  	digitalWrite(ledVERDE, LOW);
  	digitalWrite(ledAMAR, HIGH);
  	delay(3000);
  	digitalWrite(ledAMAR, LOW);
  	*/
  	
  	ligaLED(ledVERM, 1000);
  	ligaLED(ledVERDE, 2000);
    ligaLED(ledAMAR, 3000);
}

void ligaLED(int pino, int tempo){
	digitalWrite(pino, HIGH);
  	delay(tempo);
  	digitalWrite(pino, LOW);
}