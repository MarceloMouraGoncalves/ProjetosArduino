#include <dht.h>

#include <SPI.h>

#include <PCD8544.h>

#include <EEPROM.h>



dht DHT_Sensor_Interno;
dht DHT_Sensor_Externo;


bool ligarDisplay = true;

byte luzDisplay = 75;

int tempoDesejado;
int temperaturaDesejada;

bool refrigeracaoAtivada = false;

float TemperaturaInterna = 0;
float HumidadeInterna = 0;

float TemperaturaExterna = 0;
float HumidadeExterna = 0;

#define BOTAO_ESQUERDA_PIN 8
#define BOTAO_DIREITA_PIN 9 
#define BOTAO_ENTER_PIN 12

//#define DHT11_INTERNO_PIN 7
//#define DHT11_EXTERNO_PIN 8

#define RELE_REFRIGERAR_PIN 13

#define BUZZER_PIN 3


struct LinhasDisplay
{
  char Linhas[6][14];
};

struct DadosMenu
{
  char Titulo[14];
  byte Posicao;
  bool Selecionado;
  bool Modificar;
  bool MenuDeConfiguracao;
  char NomeDados[4][8];
  int Dados[4];
  int DadosIncremento[4];
  int DadosMaximo[4];
  bool ModificarDados[4];
};

struct DadosBotao
{
  bool posicaoAtual;
  bool ultimaPosicao;
  int tempo;
};

struct LinhasDisplay linhasDisplay;


void setup(){
 
  pinMode(RELE_REFRIGERAR_PIN, OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);

  
  
  Serial.begin(9600);

  BuzzerSomInicio();
  
  IniciarDisplay();
  //LuzDisplay(luzDisplay);
  LimparDisplay();
  InicializarOperacoesMenu();  
}

void loop()
{  
//   DHT_Sensor_Interno.read11(DHT11_INTERNO_PIN);
   delay(10);
//   DHT_Sensor_Externo.read11(DHT11_EXTERNO_PIN);
 
  TemperaturaInterna = DHT_Sensor_Interno.temperature;
  HumidadeInterna = DHT_Sensor_Interno.humidity;

  TemperaturaExterna = DHT_Sensor_Externo.temperature;
  HumidadeExterna = DHT_Sensor_Externo.humidity;
 

 if(TemperaturaInterna > temperaturaDesejada) 
 {
  if(!refrigeracaoAtivada)
  {
    refrigeracaoAtivada = true;
    BuzzerSomInicio();
  }
  digitalWrite(RELE_REFRIGERAR_PIN, LOW);
  Serial.println("Ligar Cooler");
 }
  else
  {
    if(refrigeracaoAtivada)
  {
    refrigeracaoAtivada = false;
    BuzzerSomInicio();
  }
   digitalWrite(RELE_REFRIGERAR_PIN, HIGH);
  }

  MostrarMenu();
  
 delay(1000);

}
