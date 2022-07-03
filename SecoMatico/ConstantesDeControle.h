const long LOOP_INTERVALO_MS = 200;

const long LOOP_CONTROLE_POSICAO = 5;
const long LOOP_CONTROLE_TEMPERATURA = 130;

enum ESTADOS_DE_CONTROLE 
{
    EstadoIndefinido,
    EstadoInicializacaoDePosicao,
    EstadoControleDePosicao,
    EstadoControleDeTemparatura,
    EstadoEmergenciaDeTemperatura,
    EstadoControleManual    
};

  