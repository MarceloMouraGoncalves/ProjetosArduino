#include "ConstantesDeControle.h"

int contadorLoopControlePosicao = 0;
int contadorLoopControleTemperatura = 0;

int DefinirEstadoAtual()
{
  contadorLoopControlePosicao++;
  contadorLoopControleTemperatura++;

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