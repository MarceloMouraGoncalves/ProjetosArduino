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

bool MotorPosicao(int pinoMotor)
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

bool Motor1Inicializacao = false;

void Motor1InicializarPosicaoMin()
{
    if(Motor1Inicializacao)
    {
        return;
    }

    if(Motor1PosicaoMin())
    {        
        Motor1RotacaoParada();
        Motor1Inicializacao = true;
        return;
    }

    Motor1RotacaoNegativa();
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

bool Motor2Inicializacao = false;

void Motor2InicializarPosicaoMin()
{
    if(Motor2Inicializacao)
    {
        return;
    }

    if(Motor2PosicaoMin())
    {
        Motor2RotacaoParada();
        Motor2Inicializacao = true;
        return;
    }

    Motor2RotacaoNegativa();
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

void InicializarControleDePosicao(int intervaloDeExecucaoMs)
{
    AnguloDeAcionamento = CalcularAnguloDeAcionamento(intervaloDeExecucaoMs);

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
    Serial.println(AlteracaoDeAngulo);
}

void InicializarPosicaoMin()
{
    Motor1InicializarPosicaoMin();
    Motor2InicializarPosicaoMin();
}

void ControlarPosicao()
{
    if(!Motor1Inicializacao || !Motor2Inicializacao)
    {
        InicializarPosicaoMin();
        return;
    }

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

