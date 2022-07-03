const float ERRO_ACUMULADO_TEMPERATURA_MAX = 50;
const float CONTROLE_POSICAO_MAX = 1;

static float IntervaloDeTempo = 1;

static float ErroDeTemperatura = 0;
static float ErroAnteriorDeTemperatura = 0;
static float ErroAcumuladoDeTemperatura = 0;

static float ConstanteP, ConstanteI, ConstanteD;

void InicializarControleDeTemparatura(long intervaloDeExecucaoMs, float constanteP, float constanteI, float constanteD)
{
    IntervaloDeTempo = intervaloDeExecucaoMs / 1000;

    ConstanteP = constanteP;
    ConstanteI = constanteI;
    ConstanteD = constanteD;
}

void CalcularErro(float temperaturaAtual, float temperaturaDesejada)
{
    ErroDeTemperatura = temperaturaAtual - temperaturaDesejada;
}

float CalcularControleP()
{
    return ConstanteP * (ErroDeTemperatura / IntervaloDeTempo);
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
      
    return ConstanteI * (ErroAcumuladoDeTemperatura / IntervaloDeTempo);   
}

float CalcularControleD()
{
    ErroAnteriorDeTemperatura = ErroDeTemperatura;
    
    return ConstanteD * ((ErroAnteriorDeTemperatura - ErroDeTemperatura) / IntervaloDeTempo);
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

    Serial.println(posicao);

    return posicao;
}