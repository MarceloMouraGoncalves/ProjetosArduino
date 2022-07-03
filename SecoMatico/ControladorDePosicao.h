#define PINO_MOTOR1_ROT_POS 37
#define PINO_MOTOR1_ROT_NEG 39
#define PINO_MOTOR2_ROT_POS 41
#define PINO_MOTOR2_ROT_NEG 43

#define PINO_MOTOR1_POSICAO_MIN 23
#define PINO_MOTOR1_POSICAO_MAX 25
#define PINO_MOTOR2_POSICAO_MIN 27
#define PINO_MOTOR2_POSICAO_MAX 29

#define MOTOR_ATIVADO LOW
#define MOTOR_PARADO HIGH
#define MOTOR_POSICAO LOW 

const long TEMPO_TOTAL_MS = 30000;
const float ANGULO_TOTAL_RAD = PI / 2;
const float ANGULO_MIN_RAD = ANGULO_TOTAL_RAD / 10;

float *AlteracaoDeAngulo;
static float AnguloDeAcionamento = 0;

bool *ptrMotor1Inicializacao;
bool *ptrMotor2Inicializacao;

float CalcularAnguloDeAcionamento(int intervaloDeExecucaoMs)
{
    float anguloPorMs = ANGULO_TOTAL_RAD / TEMPO_TOTAL_MS;    

    return anguloPorMs * intervaloDeExecucaoMs;
}

void AjustarAlteracaoDeAngulo(float *alteracaoDeAngulo)
{
    AlteracaoDeAngulo = alteracaoDeAngulo;
}

bool MotorPosicao(byte pinoMotor)
{
    return digitalRead(pinoMotor) == MOTOR_POSICAO;
}

bool Motor1PosicaoMin()
{
    return MotorPosicao(PINO_MOTOR1_POSICAO_MIN);
}

bool Motor1PosicaoMax()
{
    return MotorPosicao(PINO_MOTOR1_POSICAO_MAX);
}

bool Motor2PosicaoMin()
{
    return MotorPosicao(PINO_MOTOR2_POSICAO_MIN);
}

bool Motor2PosicaoMax()
{
    return MotorPosicao(PINO_MOTOR2_POSICAO_MAX);
}

void Motor1RotacaoParada()
{
    digitalWrite(PINO_MOTOR1_ROT_POS, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR1_ROT_NEG, MOTOR_PARADO);
}

void Motor1RotacaoPositiva()
{
    if(Motor1PosicaoMax())
    {
        Motor1RotacaoParada();
        return;
    }

    digitalWrite(PINO_MOTOR1_ROT_POS, MOTOR_ATIVADO);    
    digitalWrite(PINO_MOTOR1_ROT_NEG, MOTOR_PARADO);
}

void Motor1RotacaoNegativa()
{
    if(Motor1PosicaoMin())
    {
        Motor1RotacaoParada();
        return;
    }

    digitalWrite(PINO_MOTOR1_ROT_POS, MOTOR_PARADO);    
    digitalWrite(PINO_MOTOR1_ROT_NEG, MOTOR_ATIVADO);
}

void Motor1InicializarPosicaoMin()
{
    if(*ptrMotor1Inicializacao)
    {
        return;
    }

    if(Motor1PosicaoMin())
    {        
        Motor1RotacaoParada();
        *ptrMotor1Inicializacao = true;
        return;
    }

    Motor1RotacaoNegativa();
}

void Motor1ForcarPosicaoMax()
{
    if(Motor1PosicaoMax())
    {
        Motor1RotacaoParada();
        return;
    }

    Motor1RotacaoPositiva();
}

void Motor2RotacaoParada()
{
    digitalWrite(PINO_MOTOR2_ROT_POS, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR2_ROT_NEG, MOTOR_PARADO);
}

void Motor2RotacaoPositiva()
{
    if(Motor2PosicaoMax())
    {
        Motor2RotacaoParada();
        return;
    }

    digitalWrite(PINO_MOTOR2_ROT_POS, MOTOR_ATIVADO);
    digitalWrite(PINO_MOTOR2_ROT_NEG, MOTOR_PARADO);
}

void Motor2RotacaoNegativa()
{
    if(Motor2PosicaoMin())
    {
        Motor2RotacaoParada();
        return;
    }

    digitalWrite(PINO_MOTOR2_ROT_POS, MOTOR_PARADO);
    digitalWrite(PINO_MOTOR2_ROT_NEG, MOTOR_ATIVADO);
}

void Motor2InicializarPosicaoMin()
{
    if(*ptrMotor2Inicializacao)
    {
        return;
    }

    if(Motor2PosicaoMin())
    {
        Motor2RotacaoParada();
        *ptrMotor2Inicializacao = true;
        return;
    }

    Motor2RotacaoNegativa();
}

void Motor2ForcarPosicaoMax()
{
    if(Motor2PosicaoMax())
    {
        Motor2RotacaoParada();
        return;
    }

    Motor2RotacaoPositiva();
}

void RotacaoPositiva()
{
    Motor1RotacaoPositiva();
    Motor2RotacaoPositiva();
}

void RotacaoNegativa()
{
    Motor1RotacaoNegativa();
    Motor2RotacaoNegativa();
}

void PararRotacao()
{
    Motor1RotacaoParada();
    Motor2RotacaoParada();
}

void InicializarControleDePosicao(int intervaloDeExecucaoMs, bool *motor1Inicializacao, bool *motor2Inicializacao)
{
    AnguloDeAcionamento = CalcularAnguloDeAcionamento(intervaloDeExecucaoMs);

    ptrMotor1Inicializacao = motor1Inicializacao;
    ptrMotor2Inicializacao = motor2Inicializacao;

    pinMode(PINO_MOTOR1_ROT_POS, OUTPUT);
    pinMode(PINO_MOTOR1_ROT_NEG, OUTPUT);
    pinMode(PINO_MOTOR2_ROT_POS, OUTPUT);
    pinMode(PINO_MOTOR2_ROT_NEG, OUTPUT);

    pinMode(PINO_MOTOR1_POSICAO_MAX, INPUT);
    pinMode(PINO_MOTOR1_POSICAO_MIN, INPUT);
    pinMode(PINO_MOTOR2_POSICAO_MIN, INPUT);
    pinMode(PINO_MOTOR2_POSICAO_MAX, INPUT);

    PararRotacao();
}

void ImprimirAngulo()
{
    Serial.print("Angulo = ");
    Serial.println(*AlteracaoDeAngulo);
}

void InicializarPosicaoMin(bool *motor1Inicializacao, bool *motor2Inicializacao)
{
    ptrMotor1Inicializacao = motor1Inicializacao;
    ptrMotor2Inicializacao = motor2Inicializacao;

    Motor1InicializarPosicaoMin();
    Motor2InicializarPosicaoMin();
}

void ForcarPosicaoMax()
{
    Motor1ForcarPosicaoMax();
    Motor2ForcarPosicaoMax();
}

bool InicializacoDeMotoresCompleta()
{
    return *ptrMotor1Inicializacao && *ptrMotor2Inicializacao;
}

void ControlarPosicao()
{
    if(*AlteracaoDeAngulo > ANGULO_MIN_RAD)
    {
        RotacaoPositiva();

        *AlteracaoDeAngulo -= AnguloDeAcionamento;

        return;
    }

    if(*AlteracaoDeAngulo < ANGULO_MIN_RAD * -1)
    {
        RotacaoNegativa();

        *AlteracaoDeAngulo += AnguloDeAcionamento;

        return;
    }

    PararRotacao();
}

