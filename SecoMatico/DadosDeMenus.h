#include "ControladorDeDadosEeprom.h"

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

const byte MENUS_TOTAL = 3;

const byte CONSTANTE_P_ENDERECO = 0;
const byte CONSTANTE_I_ENDERECO = 4;
const byte CONSTANTE_D_ENDERECO = 8;
const byte CONSTANTE_TEMP_MAX = 12;
const byte CONSTANTE_TEMP_SETPOINT = 16;

struct DadosMenu DadosMenuSupervisao, DadosMenuTemperatura, DadosMenuControlePid, DadosMenuSelecionado;

void SalvarEeeprom()
{
  EepromWriteFloat(CONSTANTE_P_ENDERECO, DadosMenuControlePid.Valores[0]);
  EepromWriteFloat(CONSTANTE_I_ENDERECO, DadosMenuControlePid.Valores[1]);
  EepromWriteFloat(CONSTANTE_D_ENDERECO, DadosMenuControlePid.Valores[2]);
  EepromWriteFloat(CONSTANTE_TEMP_MAX, DadosMenuControlePid.Valores[3]);

  EepromWriteFloat(CONSTANTE_TEMP_SETPOINT, DadosMenuTemperatura.Valores[0]);
}

void CarregarEeeprom()
{
  DadosMenuControlePid.Valores[0] = EepromReadFloat(CONSTANTE_P_ENDERECO);
  DadosMenuControlePid.Valores[1] = EepromReadFloat(CONSTANTE_I_ENDERECO);
  DadosMenuControlePid.Valores[2] = EepromReadFloat(CONSTANTE_D_ENDERECO);
  DadosMenuControlePid.Valores[3] = EepromReadFloat(CONSTANTE_TEMP_MAX);

  DadosMenuTemperatura.Valores[0] = EepromReadFloat(CONSTANTE_TEMP_SETPOINT);
}

void InicializarDadosMenuSupervisao()
{
  DadosMenuSupervisao.Index = 0;

  strcpy(DadosMenuSupervisao.Titulo, "  Supervisor");
    
  strcpy(DadosMenuSupervisao.NomeDados[0], "Inicializacao");
  DadosMenuSupervisao.Mensagem[0] = true;

  strcpy(DadosMenuSupervisao.NomeDados[1], "Temp. C  ");    
  strcpy(DadosMenuSupervisao.NomeDados[2], "SetP. C  ");
  strcpy(DadosMenuSupervisao.NomeDados[3], "Controle");
    
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

  DadosMenuTemperatura.DadosIncremento[0] = 0.5;

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

  DadosMenuControlePid.DadosIncremento[0] = 0.05;
  DadosMenuControlePid.DadosIncremento[1] = 0.05;
  DadosMenuControlePid.DadosIncremento[2] = 0.05;
  DadosMenuControlePid.DadosIncremento[3] = 0.5;

  DadosMenuControlePid.Tipo = MenuDeConfiguracao;
  DadosMenuControlePid.NumeroPosicoes = 4;
}

void InicializarDadosDeMenus()
{    
    InicializarDadosMenuSupervisao();
    InicializarDadosMenuTemperatura();
    InicializarDadosMenuControlePid();

    CarregarEeeprom();
}