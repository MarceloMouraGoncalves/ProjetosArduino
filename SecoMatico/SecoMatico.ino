#include "LeituraDeTemperatura.h"
#include "ControladorDeEstados.h"

/*
  Controle de Tempratura com Fluxo De Ar em um Secador de Café a Lenha
*/

const long LOOP_INTERVALO_MS = 100;

// the setup function runs once when you press reset or power the board
void setup() 
{  
  Serial.begin(115200);

  IniciarLeituraDeTemperatura();
}

unsigned int tempoAnteriorMs = 0;        
unsigned int tempoAtualMs = 0;

// the loop function runs over and over again forever
void loop() 
{
  tempoAtualMs = millis();

  if (tempoAtualMs - tempoAnteriorMs < LOOP_INTERVALO_MS) 
  {
    return;
  }
  
  switch (DefinirEstadoAtual())
  {
    case ESTADO_AQUISICAO:
      Aquisicao();
      break;
    
    case ESTADO_CONTROLE:
      Controle();
      break;

    default:
      break;
  }
  
  tempoAnteriorMs = millis();
}

void Aquisicao()
{
  Serial.print("Aquisicao Temperatura = ");

  float temperatura = LerTemperaturaC();
  Serial.println(temperatura);
}

void Controle()
{
  Serial.println("Controle");
}