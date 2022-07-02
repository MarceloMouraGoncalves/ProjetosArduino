const long LOOP_INTERVALO_MS = 100;

const long LOOP_CONTROLE_POSICAO = 10;
const long LOOP_CONTROLE_TEMPERATURA = 600;

const float TEMPERATURA_MAX = 65;

enum ESTADOS_DE_CONTROLE 
{
    EstadoIndefinido,
    EstadoInicializacaoDePosicao,
    EstadoControleDePosicao,
    EstadoControleDeTemparatura,
    EstadoEmergenciaDeTemperatura,
    EstadoControleManual    
};

  