#include "ConstantesDeControle.h"

int contadorLoopControlePosicao = 0;
int contadorLoopControleTemperatura = 0;

int DefinirEstadoAtual(float temperatura)
{
  contadorLoopControlePosicao++;
  contadorLoopControleTemperatura++;

  if(temperatura >= TEMPERATURA_MAX)
  {
    return ESTADO_EMERGENCIA_TEMPERATURA;
  }

  if(contadorLoopControlePosicao >= LOOP_CONTROLE_POSICAO)
  {
    contadorLoopControlePosicao = 0;
    return ESTADO_CONTROLE_POSICAO;
  }

  if(contadorLoopControleTemperatura >= LOOP_CONTROLE_TEMPERATURA)
  {
    contadorLoopControleTemperatura = 0;
    return ESTADO_CONTROLE_TEMPERATURA;
  }

  return ESTADO_INDEFINIDO;
}