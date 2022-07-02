enum TipoDeMenu
{
  MenuDeSupervisao,
  MenuDeConfiguracao,
  MenuDeSelecao
};


struct DadosMenu
{
  char Titulo[14];
  byte Posicao;
  bool Selecionado;
  bool Modificar;
  TipoDeMenu Tipo;
  char NomeDados[4][14];
  bool Ocultar[4];
  bool Mensagem[4];
  float Valores[4];
  float DadosIncremento[4];
  float DadosMaximo[4];
  bool ModificarDados[4];
};

struct DadosMenu DadosMenuSupervisao, DadosMenuTemperatura;

void InicializarDadosMenuSupervisao()
{
    strcpy(DadosMenuSupervisao.Titulo, "  Supervisor");
    DadosMenuSupervisao.Posicao = 0;
    
    strcpy(DadosMenuSupervisao.NomeDados[0], "Inicializacao");
    DadosMenuSupervisao.Mensagem[0] = true;

    strcpy(DadosMenuSupervisao.NomeDados[1], "Temp. C  ");    
    strcpy(DadosMenuSupervisao.NomeDados[2], "SetP. C  ");
    strcpy(DadosMenuSupervisao.NomeDados[3], "Controle ");
    
    DadosMenuSupervisao.Tipo = MenuDeSupervisao;
}

void InicializarDadosMenuTemperatura()
{
    strcpy(DadosMenuTemperatura.Titulo, " Temperatura");
    DadosMenuTemperatura.Posicao = 1;
    
    strcpy(DadosMenuTemperatura.NomeDados[0], "");
    strcpy(DadosMenuTemperatura.NomeDados[1], "SetP. C  ");    
    strcpy(DadosMenuTemperatura.NomeDados[2], "");
    strcpy(DadosMenuTemperatura.NomeDados[3], "");
    
    DadosMenuTemperatura.Tipo = MenuDeConfiguracao;
}

void InicializarDadosDeMenus()
{    
    InicializarDadosMenuSupervisao();
    InicializarDadosMenuTemperatura();
}