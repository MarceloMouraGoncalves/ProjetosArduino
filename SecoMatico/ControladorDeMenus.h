#include "ControladorDeDisplay.h"

struct DadosMenu
{
  char Titulo[14];
  byte Posicao;
  bool Selecionado;
  bool Modificar;
  bool MenuDeConfiguracao;
  char NomeDados[4][14];
  int Dados[4];
  int DadosIncremento[4];
  int DadosMaximo[4];
  bool ModificarDados[4];
};

struct LinhasDisplay linhasDisplay;
int menuSelecionado = 0;
struct DadosMenu dadosMenuSelecao, dadosMenuSupervisao, dadosMenuDeEntrada;

String  SelecionarItem(String item, int valor, bool selecionado, bool modificar, bool menuDeConfiguracao)
{
  if (item == "")
    return "";

  if (!menuDeConfiguracao)
  {
    return "  " + item + " " + valor;
  }

  if (selecionado)
  {
    return "> " + item + " " + valor;
  }

  return "  " + item + " " + valor;
}

void GerarMenu(struct DadosMenu dados)
{
  if(dados.MenuDeConfiguracao)
  {
    strcpy(linhasDisplay.Linhas[0], dados.Titulo);
    strcpy(linhasDisplay.Linhas[1], "--------------");
  
    String tempString;
    char tempChar[14];
  
    for (int i = 0; i < 4; i++)
    {
      tempString = SelecionarItem(dados.NomeDados[i], dados.Dados[i],
                                  dados.Posicao == i + 1, dados.Modificar, dados.MenuDeConfiguracao);
  
      tempString.toCharArray(tempChar, 14);
  
      strcpy(linhasDisplay.Linhas[i + 2], tempChar);
    }

    return;
  }

  strcpy(linhasDisplay.Linhas[0], dados.Titulo);
  strcpy(linhasDisplay.Linhas[1], "--------------");
  strcpy(linhasDisplay.Linhas[2], dados.NomeDados[0]);
  strcpy(linhasDisplay.Linhas[3], dados.NomeDados[1]);
  strcpy(linhasDisplay.Linhas[4], dados.NomeDados[2]);
  strcpy(linhasDisplay.Linhas[5], dados.NomeDados[3]);
  
}

void SelecionarMenu(struct DadosMenu & dados)
{
  menuSelecionado = menuSelecionado + 1;

  if (menuSelecionado > 2)
    menuSelecionado = 0;

}

void MostrarMenu()
{
    MostrarDisplay(linhasDisplay);
}

void MostrarMenuInicial()
{
  SelecionarMenu(dadosMenuSelecao);
  GerarMenu(dadosMenuSelecao);
  MostrarDisplay(linhasDisplay);
}

void InicializarControleDeMenu()
{
    IniciarDisplay();

    strcpy(dadosMenuSelecao.Titulo, "    Selecao");
    dadosMenuSelecao.Posicao = 1;
    strcpy(dadosMenuSelecao.NomeDados[0], "Borra.");
    strcpy(dadosMenuSelecao.NomeDados[1], "Couro ");
    strcpy(dadosMenuSelecao.NomeDados[2], "Tecido");
    strcpy(dadosMenuSelecao.NomeDados[3], "");
    dadosMenuSelecao.MenuDeConfiguracao = true;

    MostrarMenuInicial();
}