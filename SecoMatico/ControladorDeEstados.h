#include "ConstantesDeControle.h"

#define PINO_CONTROLE_AUTO 20

int contadorLoopControlePosicao = 0;
int contadorLoopControleTemperatura = 0;

bool ControleManual()
{
  return digitalRead(PINO_CONTROLE_AUTO) == LOW;
}

void InicializarControladorDeEstados()
{
  pinMode(PINO_CONTROLE_AUTO, INPUT);
}

int DefinirEstadoAtual(float temperatura, bool inicializacaoCompleta)
{
  contadorLoopControlePosicao++;
  contadorLoopControleTemperatura++;

  if(ControleManual())
  {
    return EstadoControleManual;
  }

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