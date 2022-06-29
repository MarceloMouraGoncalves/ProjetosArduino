#define PINO_MOTOR1_ROT_POS 37
#define PINO_MOTOR1_ROT_NEG 39
#define PINO_MOTOR2_ROT_POS 41
#define PINO_MOTOR2_ROT_NEG 43

#define PINO_MOTOR1_FECHADO 23
#define PINO_MOTOR1_ABERTO 25
#define PINO_MOTOR2_FECHADO 27
#define PINO_MOTOR2_ABERTO 29

#define MOTOR_ATIVADO LOW
#define MOTOR_PARADO HIGH

const long TEMPO_TOTAL_MS = 48000;
const float ANGULO_TOTAL_RAD = PI / 2;
const float ANGULO_MIN_RAD = ANGULO_TOTAL_RAD / 10;

float AlteracaoDeAngulo = 0;
float AnguloDeAcionamento = 0;

float CalcularAnguloDeAcionamento(int intervaloDeExecucaoMs)
{
    float anguloPorMs = ANGULO_TOTAL_RAD / TEMPO_TOTAL_MS;    

    return anguloPorMs * intervaloDeExecucaoMs;
}

void AjustarAlteracaoDeAngulo(float alteracaoDeAngulo)
{
    AlteracaoDeAngulo = alteracaoDeAngulo;
}

void RotacaoPositiva()
{
    digitalWrite(PINO_MOTOR1_ROT_POS, MOTOR_ATIVADO);
    digitalWrite(PINO_MOTOR2_ROT_POS, MOTOR_ATIVADO);

    digitalWrite(PINO_MOTOR1_ROT_NEG, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR2_ROT_NEG, MOTOR_PARADO);
}

void RotacaoNegativa()
{
    digitalWrite(PINO_MOTOR1_ROT_POS, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR2_ROT_POS, MOTOR_PARADO);

    digitalWrite(PINO_MOTOR1_ROT_NEG, MOTOR_ATIVADO);
    digitalWrite(PINO_MOTOR2_ROT_NEG, MOTOR_ATIVADO);
}

void PararRotacao()
{
    digitalWrite(PINO_MOTOR1_ROT_POS, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR2_ROT_POS, MOTOR_PARADO);

    digitalWrite(PINO_MOTOR1_ROT_NEG, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR2_ROT_NEG, MOTOR_PARADO);
}

void InicializarControleDePosicao(int intervaloDeExecucaoMs)
{
    AnguloDeAcionamento = CalcularAnguloDeAcionamento(intervaloDeExecucaoMs);

    pinMode(PINO_MOTOR1_ROT_POS, OUTPUT);
    pinMode(PINO_MOTOR1_ROT_NEG, OUTPUT);
    pinMode(PINO_MOTOR2_ROT_POS, OUTPUT);
    pinMode(PINO_MOTOR2_ROT_NEG, OUTPUT);

    pinMode(PINO_MOTOR1_FECHADO, INPUT);
    pinMode(PINO_MOTOR1_ABERTO, INPUT);
    pinMode(PINO_MOTOR2_FECHADO, INPUT);
    pinMode(PINO_MOTOR2_ABERTO, INPUT);

    PararRotacao();
}

void ImprimirAngulo()
{
    Serial.print("Angulo = ");
    Serial.println(AlteracaoDeAngulo);
}

void ControlarAngulo()
{
    if(AlteracaoDeAngulo > ANGULO_MIN_RAD)
    {
        RotacaoPositiva();

        AlteracaoDeAngulo -= AnguloDeAcionamento;

        ImprimirAngulo();

        return;
    }

    if(AlteracaoDeAngulo < ANGULO_MIN_RAD * -1)
    {
        RotacaoNegativa();

        AlteracaoDeAngulo += AnguloDeAcionamento;

        ImprimirAngulo();

        return;
    }

    PararRotacao();
}

