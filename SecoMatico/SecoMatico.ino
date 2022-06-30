#include "LeitorDeTemperatura.h"
#include "ControladorDeEstados.h"
#include "ControladorDePosicao.h"
#include "ControladorDeTemperatura.h"

/*
  Controle de Tempratura com Fluxo De Ar em um Secador de Café a Lenha
*/

// the setup function runs once when you press reset or power the board
void setup() 
{  
  Serial.begin(115200);

  InicializarLeituraDeTemperatura();
  InicializarControleDePosicao(LOOP_INTERVALO_MS * LOOP_CONTROLE_POSICAO);
  InicializarControleDeTemparatura(LOOP_INTERVALO_MS * LOOP_CONTROLE_TEMPERATURA);
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
    case ESTADO_CONTROLE_POSICAO:
      ControleDePosicao();
      break;
    
    case ESTADO_CONTROLE_TEMPERATURA:
      ControleDeTemparatura();
      break;

    default:
      break;
  }
}

void ControleDePosicao()
{
  Serial.print("Aquisicao Temperatura = ");

  float temperatura = LerTemperaturaC();
  Serial.println(temperatura);

  ControlarPosicao();
}

void ControleDeTemparatura()
{
  float temperaturaAtual = LerTemperaturaC();
  float temperaturaDesejada = 40;

  float posicao = CalcularControle(temperaturaAtual, temperaturaDesejada);

  Serial.println("Controle");  
}