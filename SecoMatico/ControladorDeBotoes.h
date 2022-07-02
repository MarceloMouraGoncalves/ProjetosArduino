#define PINO_BOTAO_ESQUERDA 31
#define PINO_BOTAO_ENTRAR 33
#define PINO_BOTAO_DIREITA 35

#define BOTAO_PRESSIONADO HIGH

const int LOOP_BOTAO_PRESSIONADO = 2;

bool BotaoEsquerdaPressionado, BotaoEntradaPressionado, BotaoDireitaPressionado;
int BotaoLoop;

bool BotaoPressionado(byte pinoBotao)
{
    return digitalRead(pinoBotao) == BOTAO_PRESSIONADO;
}

void IndentificarBotaoPressinado(byte pinoBotao, bool *pressionado)
{
    if(BotaoLoop > LOOP_BOTAO_PRESSIONADO)
    {
        BotaoLoop = 0;
    }
    
    BotaoLoop++;

    bool pressionadoTemp = BotaoPressionado(pinoBotao);

    if(pressionadoTemp != *pressionado)
    {
        *pressionado = !*pressionado;
        BotaoLoop = 0;
        return;
    }

    if(BotaoLoop >= LOOP_BOTAO_PRESSIONADO)
    {
        *pressionado = pressionadoTemp;
        BotaoLoop = 0;        
    }    
}

void IndentificarBotoesPressinados()
{
    IndentificarBotaoPressinado(PINO_BOTAO_ESQUERDA, &BotaoEsquerdaPressionado);
    IndentificarBotaoPressinado(PINO_BOTAO_ENTRAR, &BotaoEntradaPressionado);
    IndentificarBotaoPressinado(PINO_BOTAO_DIREITA, &BotaoDireitaPressionado);
}

void InitializarControladorDeBotoes()
{
    pinMode(PINO_BOTAO_ESQUERDA, INPUT);
    pinMode(PINO_BOTAO_DIREITA, INPUT);
    pinMode(PINO_BOTAO_ENTRAR, INPUT);
}