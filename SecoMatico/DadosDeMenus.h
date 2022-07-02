enum TipoDeMenu
{
  MenuDeSupervisao,
  MenuDeConfiguracao,
  MenuDeSelecao
};


struct DadosMenu
{
  byte Index;
  char Titulo[14];
  byte Posicao;
  bool Selecionado;
  bool Modificar;
  byte NumeroPosicoes;
  TipoDeMenu Tipo;
  char NomeDados[4][14];
  bool Ocultar[4];
  bool Mensagem[4];
  float Valores[4];
  float DadosIncremento[4];
  float DadosMaximo[4];
  bool ModificarDados[4];
};

const int MENUS_TOTAL = 3;

struct DadosMenu DadosMenuSupervisao, DadosMenuTemperatura, DadosMenuControlePid, DadosMenuSelecionado;

void InicializarDadosMenuSupervisao()
{
  DadosMenuSupervisao.Index = 0;

  strcpy(DadosMenuSupervisao.Titulo, "  Supervisor");
    
  strcpy(DadosMenuSupervisao.NomeDados[0], "Inicializacao");
  DadosMenuSupervisao.Mensagem[0] = true;

  strcpy(DadosMenuSupervisao.NomeDados[1], "Temp. C  ");    
  strcpy(DadosMenuSupervisao.NomeDados[2], "SetP. C  ");
  strcpy(DadosMenuSupervisao.NomeDados[3], "Controle ");
    
  DadosMenuSupervisao.Tipo = MenuDeSupervisao;
}

void InicializarDadosMenuTemperatura()
{
  DadosMenuTemperatura.Index = 1;
    
  strcpy(DadosMenuTemperatura.Titulo, " Temperatura");
    
  strcpy(DadosMenuTemperatura.NomeDados[0], "SetP. C");
  strcpy(DadosMenuTemperatura.NomeDados[1], "");    
  strcpy(DadosMenuTemperatura.NomeDados[2], "");
  strcpy(DadosMenuTemperatura.NomeDados[3], "");
    
  DadosMenuTemperatura.NumeroPosicoes = 1;
  DadosMenuTemperatura.Tipo = MenuDeConfiguracao;
}

void InicializarDadosMenuControlePid()
{
  DadosMenuControlePid.Index = 2;

  strcpy(DadosMenuControlePid.Titulo, " Controle PID");
  strcpy(DadosMenuControlePid.NomeDados[0], "Cons. P");
  strcpy(DadosMenuControlePid.NomeDados[1], "Cons. I");    
  strcpy(DadosMenuControlePid.NomeDados[2], "Cons. D");
  strcpy(DadosMenuControlePid.NomeDados[3], "T.M. C");
  
  DadosMenuControlePid.Tipo = MenuDeConfiguracao;
  DadosMenuControlePid.NumeroPosicoes = 4;
}

void InicializarDadosDeMenus()
{    
    InicializarDadosMenuSupervisao();
    InicializarDadosMenuTemperatura();
    InicializarDadosMenuControlePid();
}