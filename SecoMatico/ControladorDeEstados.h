#include "ConstantesDeControle.h"

int contadorLoopControlePosicao = 0;
int contadorLoopControleTemperatura = 0;

int DefinirEstadoAtual(float temperatura, bool inicializacaoCompleta)
{
  contadorLoopControlePosicao++;
  contadorLoopControleTemperatura++;

  if(temperatura >= TEMPERATURA_MAX)
  {
    return EstadoEmergenciaDeTemperatura;
  }

  if(!inicializacaoCompleta)
  {
    return EstadoInicializacaoDePosicao;
  }

  if(contadorLoopControlePosicao >= LOOP_CONTROLE_POSICAO)
  {
    contadorLoopControlePosicao = 0;
    return EstadoControleDePosicao;
  }

  if(contadorLoopControleTemperatura >= LOOP_CONTROLE_TEMPERATURA)
  {
    contadorLoopControleTemperatura = 0;
    return EstadoControleDeTemparatura;
  }

  return EstadoIndefinido;
}