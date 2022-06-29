const int LOOP_AQUISICAO = 10;
const int LOOP_CONTROLE = 600;

const int ESTADO_INDEFINIDO = -1;
const int ESTADO_AQUISICAO = 1;
const int ESTADO_CONTROLE = 2;

int contadorLoopAquisicao = 0;
int contadorLoopControle = 0;

int DefinirEstadoAtual()
{
  contadorLoopAquisicao++;
  contadorLoopControle++;

  if(contadorLoopAquisicao >= LOOP_AQUISICAO)
  {
    contadorLoopAquisicao = 0;
    return ESTADO_AQUISICAO;
  }

  if(contadorLoopControle >= LOOP_CONTROLE)
  {
    contadorLoopControle = 0;
    return ESTADO_CONTROLE;
  }

  return ESTADO_INDEFINIDO;
}