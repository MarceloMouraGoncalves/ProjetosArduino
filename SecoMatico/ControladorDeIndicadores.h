#define PINO_INDICADOR_BUZZER 12
#define PINO_INDICADOR_SIRENE 45
#define PINO_INDICADOR_BOM 47
#define PINO_INDICADOR_ALARME 49
#define PINO_INDICADOR_EMERGENCIA 51

#define INDICADOR_ATIVADO LOW
#define INDICADOR_DESATIVADO HIGH

void BuzzerSomInicio()
{
  tone(PINO_INDICADOR_BUZZER, 262, 250);
}

void BuzzerSomFinal()
{
  tone(PINO_INDICADOR_BUZZER, 100, 850);      
}

void LimparIndicadores()
{
    digitalWrite(PINO_INDICADOR_SIRENE, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_BOM, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_ALARME, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_EMERGENCIA, INDICADOR_DESATIVADO);
}

void AtivarIndicadorBom()
{
    digitalWrite(PINO_INDICADOR_SIRENE, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_BOM, INDICADOR_ATIVADO);
    digitalWrite(PINO_INDICADOR_ALARME, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_EMERGENCIA, INDICADOR_DESATIVADO);
}

void AtivarIndicadorAlarm()
{
    digitalWrite(PINO_INDICADOR_SIRENE, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_BOM, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_ALARME, INDICADOR_ATIVADO);
    digitalWrite(PINO_INDICADOR_EMERGENCIA, INDICADOR_DESATIVADO);    
}

void AtivarIndicadorEmergencia()
{
    digitalWrite(PINO_INDICADOR_SIRENE, INDICADOR_ATIVADO);
    digitalWrite(PINO_INDICADOR_BOM, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_ALARME, INDICADOR_DESATIVADO);
    digitalWrite(PINO_INDICADOR_EMERGENCIA, INDICADOR_ATIVADO);
}

void InicializarControladorDeIndicadores()
{
    pinMode(PINO_INDICADOR_BUZZER,OUTPUT);
    pinMode(PINO_INDICADOR_SIRENE, OUTPUT);
    pinMode(PINO_INDICADOR_BOM, OUTPUT);
    pinMode(PINO_INDICADOR_ALARME, OUTPUT);
    pinMode(PINO_INDICADOR_EMERGENCIA, OUTPUT);

    BuzzerSomInicio();
}