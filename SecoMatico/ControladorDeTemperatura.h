const float CONSTANTE_P = 1;
const float CONSTANTE_I = 0.25;
const float CONSTANTE_D = 0.25;

const float ERRO_ACUMULADO_TEMPERATURA_MAX = 50;
const float CONTROLE_POSICAO_MAX = 1;

float IntervaloDeTempo = 1;

float ErroDeTemperatura = 0;
float ErroAnteriorDeTemperatura = 0;
float ErroAcumuladoDeTemperatura = 0;

void InicializarControleDeTemparatura(long intervaloDeExecucaoMs)
{
    IntervaloDeTempo = intervaloDeExecucaoMs / 1000;
}

void CalcularErro(float temperaturaAtual, float temperaturaDesejada)
{
    ErroDeTemperatura = temperaturaAtual - temperaturaDesejada;
}

float CalcularControleP()
{
    return CONSTANTE_P * (ErroDeTemperatura / IntervaloDeTempo);
}

float CalcularControleI()
{
    ErroAcumuladoDeTemperatura += ErroDeTemperatura;

    if(ErroAcumuladoDeTemperatura > ERRO_ACUMULADO_TEMPERATURA_MAX)
    {
        ErroAcumuladoDeTemperatura = ERRO_ACUMULADO_TEMPERATURA_MAX;
    }
    if(ErroAcumuladoDeTemperatura < ERRO_ACUMULADO_TEMPERATURA_MAX * -1) 
    {
        ErroAcumuladoDeTemperatura = ERRO_ACUMULADO_TEMPERATURA_MAX * -1;
    }
      
    return CONSTANTE_I * (ErroAcumuladoDeTemperatura / IntervaloDeTempo);   
}

float CalcularControleD()
{
    ErroAnteriorDeTemperatura = ErroDeTemperatura;
    
    return CONSTANTE_D * ((ErroAnteriorDeTemperatura - ErroDeTemperatura) / IntervaloDeTempo);
}

float CalcularControle(float temperaturaAtual, float temperaturaDesejada)
{
    CalcularErro(temperaturaAtual, temperaturaDesejada);

      float posicao = CalcularControleP() + CalcularControleI() + CalcularControleD();
      
      if (posicao > CONTROLE_POSICAO_MAX)
      {
             posicao = CONTROLE_POSICAO_MAX;
      }
      if (posicao < CONTROLE_POSICAO_MAX * -1)
      {
             posicao = CONTROLE_POSICAO_MAX * -1;
      }

      return posicao;
}