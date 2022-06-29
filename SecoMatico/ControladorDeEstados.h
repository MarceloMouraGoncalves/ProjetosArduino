#include "ConstantesDeControle.h"

int contadorLoopAquisicao = 0;
int contadorLoopControle = 0;

int DefinirEstadoAtual()
{
  contadorLoopAquisicao++;
  contadorLoopControle++;

  if(contadorLoopAquisicao >= LOOP_AQUISICAO)
  {
    contadorLoopAquisicao = 0;
    return ESTADO_AQUISICAO;
  }

  if(contadorLoopControle >= LOOP_CONTROLE)
  {
    contadorLoopControle = 0;
    return ESTADO_CONTROLE;
  }

  return ESTADO_INDEFINIDO;
}