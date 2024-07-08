// C++ code
//
// Criação da nossa classe
// Cabeçalho / Inicialiação - Arquivo.h

class TEMPO{
	private:
  		int horas, minutos, segundos;

	public:
  		TEMPO(); 						//Construtor 0
  		TEMPO(int hh, int mm, int ss); 	//Construtor 1
  		void configTime(int, int, int);
  		void imprimeTime();
  		~TEMPO() { };
};

// Criação dos nosso métodos
// Arquivo.cpp
// Identificador de Escopo ::
TEMPO::TEMPO(){
	horas = 0;
  	minutos = 0;
  	segundos = 0;
}

TEMPO::TEMPO(int hh, int mm, int ss){
	configTime(hh, mm, ss);
}

void TEMPO::configTime(int hh, int mm, int ss){
	horas = hh;
  	minutos = mm;
  	segundos = ss;
}

void TEMPO::imprimeTime(){
Serial.print(horas);
Serial.print(":");
Serial.print(minutos);
Serial.print(":");
Serial.println(segundos);
}


TEMPO padrao;
TEMPO personalizado(20, 49, 59);

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
	padrao.imprimeTime();
  	personalizado.imprimeTime();
  	delay(1000);
}





