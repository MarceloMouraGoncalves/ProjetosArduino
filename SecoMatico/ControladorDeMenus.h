#include "ControladorDeDisplay.h"
#include "DadosDeMenus.h"

struct LinhasDisplay linhasDisplay;
int menuSelecionado = 0;

String  SelecionarItem(String item, float valor, bool selecionado, bool modificar, bool menuDeConfiguracao)
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
        if(dados.Ocultar[i])
        {
            break;
        }

        tempString = SelecionarItem(dados.NomeDados[i], dados.Valores[i],
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


void MostrarMenu()
{
    MostrarDisplay(linhasDisplay);
}

void MostrarMenuInicial()
{
    GerarMenu(DadosMenuSupervisao);
    MostrarMenu();
}


void InicializarControleDeMenu()
{
    IniciarDisplay();
    InicializarDadosDeMenus();
    MostrarMenuInicial();
}