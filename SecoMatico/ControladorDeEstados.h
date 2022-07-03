#include "ConstantesDeControle.h"

#define PINO_CONTROLE_AUTO 20

bool ControleManual()
{
  return digitalRead(PINO_CONTROLE_AUTO) == LOW;
}

void InicializarControladorDeEstados()
{
  pinMode(PINO_CONTROLE_AUTO, INPUT);;
}

int DefinirEstadoAtual(unsigned long int contadorLoopControlePosicao, unsigned long int contadorLoopControleTemperatura, float temperatura, float temperaturaMax, bool inicializacaoCompleta)
{   
  if(ControleManual())
  {
    return EstadoControleManual;
  }

  if(temperatura >= temperaturaMax)
  {
    return EstadoEmergenciaDeTemperatura;
  }

  if(!inicializacaoCompleta)
  {
    return EstadoInicializacaoDePosicao;
  }
  
  if(contadorLoopControleTemperatura >= LOOP_CONTROLE_TEMPERATURA)
  {
    return EstadoControleDeTemparatura;
  }

  if(contadorLoopControlePosicao >= LOOP_CONTROLE_POSICAO)
  {
    return EstadoControleDePosicao;
  }

  return EstadoIndefinido;
}