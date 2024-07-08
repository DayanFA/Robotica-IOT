// C++ code
//

struct alunos{
	String name;
  	int idade;
  	float altura;
};

alunos Victor = {"Victor Lima", 19, 1.81};
alunos Pedro = {"Pedro Vitor Gomes Lima", 18, 1.67};

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{	
  	Pedro.idade = 21;
	Serial.print("O nome completo e: ");
  	Serial.println(Pedro.name);
  	Serial.print("A idade e: ");
  	Serial.println(Pedro.idade);
  	Serial.print("A altura e: ");
  	Serial.println(Pedro.altura);
  
  	delay(1000);
}