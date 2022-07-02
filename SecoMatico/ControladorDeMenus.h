#include "ControladorDeDisplay.h"
#include "DadosDeMenus.h"
#include "ControladorDeBotoes.h"

struct LinhasDisplay linhasDisplay;
int NumeroMenuSelecionado;

void SalvarDadosMenu()
{
  if(NumeroMenuSelecionado == DadosMenuSupervisao.Index)
  {
    DadosMenuSupervisao = DadosMenuSelecionado;
  }

  if(NumeroMenuSelecionado == DadosMenuTemperatura.Index)
  {
    DadosMenuTemperatura = DadosMenuSelecionado;
  }

  if(NumeroMenuSelecionado == DadosMenuControlePid.Index)
  {
    DadosMenuControlePid = DadosMenuSelecionado;
  }

  SalvarEeeprom();
}

void ModificarValor()
{
  byte posicaoValor = DadosMenuSelecionado.Posicao - 1;

  if(BotaoDireitaPressionado)
  {
    DadosMenuSelecionado.Valores[posicaoValor] += DadosMenuSelecionado.DadosIncremento[posicaoValor];
    SalvarDadosMenu();
  }

  if(BotaoEsquerdaPressionado)
  {
    DadosMenuSelecionado.Valores[posicaoValor] -= DadosMenuSelecionado.DadosIncremento[posicaoValor];
    SalvarDadosMenu();
  }
}

void SelecionarValor()
{
  byte posicaoValor = DadosMenuSelecionado.Posicao - 1;

  if(BotaoEntradaPressionado)
  {
    DadosMenuSelecionado.ModificarDados[posicaoValor] = !DadosMenuSelecionado.ModificarDados[posicaoValor];
  }

  if(DadosMenuSelecionado.ModificarDados[posicaoValor])
  {
    ModificarValor();
    return;
  }

  if(BotaoDireitaPressionado)
  {
    DadosMenuSelecionado.Posicao++;    
  }

  if(BotaoEsquerdaPressionado)
  {
    DadosMenuSelecionado.Posicao--;
  }

  if(DadosMenuSelecionado.Posicao < 0)
  {
    DadosMenuSelecionado.Posicao = 0;
    DadosMenuSelecionado.Selecionado = false;
  }

  if(DadosMenuSelecionado.Posicao > DadosMenuSelecionado.NumeroPosicoes)
  {
    DadosMenuSelecionado.Posicao = 0;
    DadosMenuSelecionado.Selecionado = false;
  }
}

void SelecionarNumeroMenu()
{
  if(BotaoEntradaPressionado)
  {
    if(DadosMenuSelecionado.Tipo == MenuDeConfiguracao)
    {
      DadosMenuSelecionado.Selecionado = true;

      if(DadosMenuSelecionado.Posicao == 0)
      {
        DadosMenuSelecionado.Posicao = 1;
      }
    }    
  }
  
  if(DadosMenuSelecionado.Selecionado)
  {
    SelecionarValor();
    return;
  }

  if(BotaoDireitaPressionado)
  {
    NumeroMenuSelecionado++;    
  }

  if(BotaoEsquerdaPressionado)
  {
    NumeroMenuSelecionado--;
  }

  if(NumeroMenuSelecionado >= MENUS_TOTAL)
  {
    NumeroMenuSelecionado = 0;
  }

  if(NumeroMenuSelecionado < 0)
  {
    NumeroMenuSelecionado = MENUS_TOTAL - 1;
  }  
}

String SelecionarItem(String item, float valor, bool selecionado, bool modificar, TipoDeMenu tipoDeMenu)
{
  if (item == "")
    return "";

  if (tipoDeMenu == MenuDeSupervisao)
  {
    return item + " " + valor;
  }

  if (modificar)
  {
    return ">>" + item + " " + valor;
  }

  if (selecionado)
  {
    return "> " + item + " " + valor;
  }

  return "  " + item + " " + valor;
}

void GerarMenu()
{
  if(DadosMenuSelecionado.Tipo != MenuDeSelecao)
  {
    strcpy(linhasDisplay.Linhas[0], DadosMenuSelecionado.Titulo);

    strcpy(linhasDisplay.Linhas[1], "--------------");

    String tempString;
    char tempChar[14];
  
    for (int i = 0; i < 4; i++)
    {
        if(DadosMenuSelecionado.Ocultar[i])
        {
            break;
        }

        tempString = SelecionarItem(DadosMenuSelecionado.NomeDados[i], DadosMenuSelecionado.Valores[i],
            DadosMenuSelecionado.Posicao == i + 1, DadosMenuSelecionado.ModificarDados[i], DadosMenuSelecionado.Tipo);
  
        tempString.toCharArray(tempChar, 15);
  
        strcpy(linhasDisplay.Linhas[i + 2], tempChar);
    }

    return;
  }

  strcpy(linhasDisplay.Linhas[0], DadosMenuSelecionado.Titulo);
  strcpy(linhasDisplay.Linhas[1], "--------------");
  strcpy(linhasDisplay.Linhas[2], DadosMenuSelecionado.NomeDados[0]);
  strcpy(linhasDisplay.Linhas[3], DadosMenuSelecionado.NomeDados[1]);
  strcpy(linhasDisplay.Linhas[4], DadosMenuSelecionado.NomeDados[2]);
  strcpy(linhasDisplay.Linhas[5], DadosMenuSelecionado.NomeDados[3]);
  
}

void MostrarMenu()
{
  MostrarDisplay(linhasDisplay);  
}

void SelecionarNovoDadosMenu(DadosMenu dados)
{
  if(DadosMenuSelecionado.Index != dados.Index)
  {
    DadosMenuSelecionado = dados;
  }  
    
  GerarMenu();
}

void SelecionarDadosMenu()
{
  if(NumeroMenuSelecionado == DadosMenuSupervisao.Index)
  {
    SelecionarNovoDadosMenu(DadosMenuSupervisao);
  }

  if(NumeroMenuSelecionado == DadosMenuTemperatura.Index)
  {
    SelecionarNovoDadosMenu(DadosMenuTemperatura);
  }

  if(NumeroMenuSelecionado == DadosMenuControlePid.Index)
  {
    SelecionarNovoDadosMenu(DadosMenuControlePid);
  }
}

void AtualizarMenu()
{
  IndentificarBotoesPressinados();
  SelecionarNumeroMenu();
  SelecionarDadosMenu();
  MostrarMenu();
}

void InicializarControleDeMenu()
{  
  InicializarDisplay();
  InicializarDadosDeMenus();
  InitializarControladorDeBotoes();
  DadosMenuSelecionado = DadosMenuSupervisao;
}