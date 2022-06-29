#include "LeituraDeTemperatura.h"
#include "ControladorDeEstados.h"
#include "ControladorDePosicao.h"

/*
  Controle de Tempratura com Fluxo De Ar em um Secador de Café a Lenha
*/

// the setup function runs once when you press reset or power the board
void setup() 
{  
  Serial.begin(115200);

  InicializarLeituraDeTemperatura();
  InicializarControleDePosicao(LOOP_INTERVALO_MS * LOOP_AQUISICAO);
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
  
  tempoAnteriorMs = tempoAtualMs;

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
}

void Aquisicao()
{
  Serial.print("Aquisicao Temperatura = ");

  float temperatura = LerTemperaturaC();
  Serial.println(temperatura);

  ControlarAngulo();
}

void Controle()
{
  Serial.println("Controle");  
}