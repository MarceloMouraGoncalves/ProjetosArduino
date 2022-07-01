
struct DadosMenu
{
  char Titulo[14];
  byte Posicao;
  bool Selecionado;
  bool Modificar;
  bool MenuDeConfiguracao;
  char NomeDados[4][14];
  float Dados[4];
  float DadosIncremento[4];
  float DadosMaximo[4];
  bool ModificarDados[4];
};

struct DadosMenu DadosMenuSupervisao;

void InicializarDadosMenuSupervisao()
{
    strcpy(DadosMenuSupervisao.Titulo, "  Supervisor");
    DadosMenuSupervisao.Posicao = 0;
    
    strcpy(DadosMenuSupervisao.NomeDados[0], "Temp.C");
    
    strcpy(DadosMenuSupervisao.NomeDados[1], "SetP.C");
    strcpy(DadosMenuSupervisao.NomeDados[2], "Ctrle");
    strcpy(DadosMenuSupervisao.NomeDados[3], "Tempo");
    DadosMenuSupervisao.MenuDeConfiguracao = true;
}

void InicializarDadosDeMenus()
{    
    InicializarDadosMenuSupervisao();
}