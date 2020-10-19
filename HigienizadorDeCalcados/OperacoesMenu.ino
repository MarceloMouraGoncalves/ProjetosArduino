



bool botaoEnterPressionado = false;
bool botaoDireitaPressionado = false;
bool botaoEsquerdaPressionado = false;

long botaoEnterPressionadoTempoTempo = 0;
long botaoDireitaPressionadoTempo = 0;
long botaoEsquerdaPressionadoTempo = 0;

bool botaoEnterTempPressionado = false;
bool botaoDireitaTempPressionado = false;
bool botaoEsquerdaTempPressionado = false;

bool botaoOkMudou = false;
bool botaoCimaMudou = false;
bool botaoBaixoMudou = false;


byte menuSelecionado = 0;

struct DadosMenu dadosMenuSensores, dadosMenuConfiguracao, dadosMenuSupervisor;

void InicializarOperacoesMenu()
{
  pinMode(BOTAO_DIREITA_PIN, INPUT_PULLUP);
  pinMode(BOTAO_ENTER_PIN, INPUT_PULLUP);
  pinMode(BOTAO_ESQUERDA_PIN, INPUT_PULLUP);


  strcpy(dadosMenuConfiguracao.Titulo, "Configuracao");
  dadosMenuConfiguracao.Posicao = 0;
  strcpy(dadosMenuConfiguracao.NomeDados[0], "Tempo-h");
  dadosMenuConfiguracao.Dados[0] = 0;
  dadosMenuConfiguracao.DadosIncremento[0] = 1;
  dadosMenuConfiguracao.DadosMaximo[0] = 24;
  strcpy(dadosMenuConfiguracao.NomeDados[1], "Tempo-m");
  dadosMenuConfiguracao.Dados[1] = 0;
  dadosMenuConfiguracao.DadosIncremento[1] = 1;
  dadosMenuConfiguracao.DadosMaximo[1] = 59;
  strcpy(dadosMenuConfiguracao.NomeDados[2], "TempI-C");
  dadosMenuConfiguracao.Dados[2] = 0;
  dadosMenuConfiguracao.DadosIncremento[2] = 1;
  dadosMenuConfiguracao.DadosMaximo[2] = 99;
  //strcpy(dadosMenuConfiguracao.NomeDados[3], "Luz");
  //dadosMenuConfiguracao.Dados[3] = 0;
  //dadosMenuConfiguracao.DadosIncremento[3] = 5;
  //dadosMenuConfiguracao.DadosMaximo[3] = 100;
  dadosMenuConfiguracao.MenuDeConfiguracao = true;

  strcpy(dadosMenuSensores.Titulo, "  Sensores");
  dadosMenuSensores.Posicao = 0;
  strcpy(dadosMenuSensores.NomeDados[0], "TempI-C");
  dadosMenuSensores.Dados[0] = 0;
  strcpy(dadosMenuSensores.NomeDados[1], "HumI-%");
  dadosMenuSensores.Dados[1] = 0;
  strcpy(dadosMenuSensores.NomeDados[2], "TempE-C");
  dadosMenuSensores.Dados[2] = 0;
  strcpy(dadosMenuSensores.NomeDados[3], "HumE-%");
  dadosMenuSensores.Dados[3] = 0;
  dadosMenuSensores.MenuDeConfiguracao = false;

  strcpy(dadosMenuSupervisor.Titulo, "  Supervisor");
  dadosMenuSupervisor.Posicao = 0;
  strcpy(dadosMenuSupervisor.NomeDados[0], "TempI-C");
  dadosMenuSupervisor.Dados[0] = TemperaturaInterna;
  strcpy(dadosMenuSupervisor.NomeDados[1], "HumdI-%");
  dadosMenuSupervisor.Dados[1] = HumidadeInterna;
  strcpy(dadosMenuSupervisor.NomeDados[2], "TempE-C");
  dadosMenuSupervisor.Dados[2] = TemperaturaExterna;
  strcpy(dadosMenuSupervisor.NomeDados[3], "HumdE-%");
  dadosMenuSupervisor.Dados[3] = HumidadeExterna;
  dadosMenuSupervisor.MenuDeConfiguracao = false;

  CarregarValoresEeprom();

}

int tempoDeOperacaoMenu = 50;
long tempoUltimaOperacaoMenu = 0;

void MostrarMenu()
{
  LerBotoes();
  
  long tempoAtual = millis();

  AtualizarValoresDosSensores();

  if(tempoAtual - tempoUltimaOperacaoMenu < tempoDeOperacaoMenu)
    return;

  LerBotMenu();
  
  struct DadosMenu dados;
  DadosDoMenuSelecionado(dados);
  GerarMenu(dados);
  MostrarDisplay(linhasDisplay);

  LuzDisplay(luzDisplay);

  tempoUltimaOperacaoMenu = millis();

  for (int i = 0; i < 6; i++)
  {
    Serial.println(linhasDisplay.Linhas[i]);
  }

}

void AtualizarValoresDosSensores()
{
  dadosMenuSupervisor.Dados[0] = TemperaturaInterna;
  dadosMenuSupervisor.Dados[1] = HumidadeInterna;
  dadosMenuSupervisor.Dados[2] = TemperaturaExterna;
  dadosMenuSupervisor.Dados[3] = HumidadeExterna;  
}


void DadosDoMenuSelecionado(struct DadosMenu &dados)
{
  if (menuSelecionado == 0)
  {
    dados = dadosMenuSupervisor;
    return;
  }

  if (menuSelecionado == 1)
  {
    dados = dadosMenuSensores;
    return;
  }

  dados = dadosMenuConfiguracao;
}

void LerBotMenu()
{
  struct DadosMenu dados;

  DadosDoMenuSelecionado(dados);

  if (menuSelecionado == 0)
  {
    if (botaoDireitaPressionado)
    {
      IncrementarPosicao(dadosMenuSupervisor);
      botaoDireitaPressionado = false;
    }

    if (botaoEsquerdaPressionado)
    {
      DecrementarPosicao(dadosMenuSupervisor);
      botaoEsquerdaPressionado = false;
    }

    if (botaoEnterPressionado)
    {
      SelecionarMenu(dadosMenuSupervisor);
      botaoEnterPressionado = false;
    }
  }

  if (menuSelecionado == 1)
  {
    if (botaoDireitaPressionado)
    {
      IncrementarPosicao(dadosMenuSensores);
      botaoDireitaPressionado = false;
    }

    if (botaoEsquerdaPressionado)
    {
      DecrementarPosicao(dadosMenuSensores);
      botaoEsquerdaPressionado = false;
    }

    if (botaoEnterPressionado)
    {
      SelecionarMenu(dadosMenuSensores);
      botaoEnterPressionado = false;
    }
  }

  if (menuSelecionado == 2)
  {
    if (botaoDireitaPressionado)
    {
      IncrementarPosicao(dadosMenuConfiguracao);
      botaoDireitaPressionado = false;
    }

    if (botaoEsquerdaPressionado)
    {
      DecrementarPosicao(dadosMenuConfiguracao);
      botaoEsquerdaPressionado = false;
    }

    if (botaoEnterPressionado)
    {
      SelecionarMenu(dadosMenuConfiguracao);
      botaoEnterPressionado = false;
    }
  }

}


long ultimaOperacaoBotoes = 0;
int tempoOperacaoBotoes = 5;

void LerBotoes()
{
  long botaoTempo = millis();

  if(botaoTempo - ultimaOperacaoBotoes < tempoOperacaoBotoes)
    return;
  
  bool botaoPosicao = digitalRead(BOTAO_DIREITA_PIN);

  if(botaoDireitaTempPressionado != botaoPosicao)
  {
    botaoDireitaTempPressionado = botaoPosicao;
    botaoDireitaPressionadoTempo = millis();    
  }

  botaoTempo = millis();
  
  if(botaoTempo - botaoDireitaPressionadoTempo > 25)
  {
    if(botaoDireitaTempPressionado)
      botaoDireitaPressionado = botaoDireitaTempPressionado;
    
    botaoDireitaPressionadoTempo = millis();
  }

  botaoTempo = millis();

  botaoPosicao = digitalRead(BOTAO_ENTER_PIN);

  if(botaoEnterTempPressionado != botaoPosicao)
  {
    botaoEnterTempPressionado = botaoPosicao;
    botaoEnterPressionadoTempoTempo = millis();
  }

  if(botaoTempo - botaoEnterPressionadoTempoTempo > 25)
  {
    if(botaoEnterTempPressionado)
    {
      botaoEnterPressionado = botaoEnterTempPressionado;
      Serial.println("Botao Enter");
    }
      
    botaoEnterPressionadoTempoTempo = millis();    
  }

  botaoTempo = millis();

  botaoPosicao = digitalRead(BOTAO_ESQUERDA_PIN);

  if(botaoEsquerdaTempPressionado != botaoPosicao)
  {
    botaoEsquerdaTempPressionado = botaoPosicao;
    botaoEsquerdaPressionadoTempo = millis();
  }

  if(botaoTempo - botaoEsquerdaPressionadoTempo > 25)
  {
    if(botaoEsquerdaTempPressionado)
      botaoEsquerdaPressionado = botaoEsquerdaTempPressionado;
      
    botaoEsquerdaPressionadoTempo = millis();  
  }

  ultimaOperacaoBotoes = millis();
}


bool BotaoPressionadoZ(int pinoBotao)
{
  if (digitalRead(pinoBotao))
  {
    for (int i = 0; i < 10; i++)
    {
      delay(25);
      if (!digitalRead(pinoBotao))
      {        
        return true;
      }
    }
  }

  return false;
}

void IncrementarPosicao(struct DadosMenu & dados)
{
  
  if (!dados.MenuDeConfiguracao)
    return;

  if (dados.Modificar)
  {
    dados.Dados[dados.Posicao - 1] = dados.Dados[dados.Posicao - 1] +
                                     dados.DadosIncremento[dados.Posicao - 1];

    if (dados.Dados[dados.Posicao - 1] < 0)
      dados.Dados[dados.Posicao - 1] = dados.DadosMaximo[dados.Posicao - 1];

    if (dados.Dados[dados.Posicao - 1] > dados.DadosMaximo[dados.Posicao - 1])
      dados.Dados[dados.Posicao - 1] = 0;

    return;
  }

  dados.Posicao = dados.Posicao - 1;

  if (dados.Posicao < 0)
    dados.Posicao = 4;

}

void DecrementarPosicao(struct DadosMenu & dados)
{
  
  if (!dados.MenuDeConfiguracao)
    return;

  if (dados.Modificar)
  {
    dados.Dados[dados.Posicao - 1] = dados.Dados[dados.Posicao - 1] -
                                     dados.DadosIncremento[dados.Posicao - 1];

    if (dados.Dados[dados.Posicao - 1] < 0)
      dados.Dados[dados.Posicao - 1] = dados.DadosMaximo[dados.Posicao - 1];

    if (dados.Dados[dados.Posicao - 1] > dados.DadosMaximo[dados.Posicao - 1])
      dados.Dados[dados.Posicao - 1] = dados.DadosMaximo[dados.Posicao - 1];    

    return;
  }

  dados.Posicao = dados.Posicao + 1;

  if (dados.Posicao > 4)
    dados.Posicao = 0;

}

void SelecionarMenu(struct DadosMenu & dados)
{
  
  if (dados.MenuDeConfiguracao)
  {
    if (dados.Posicao > 0)
    {
      dados.Modificar = !dados.Modificar;

      if(!dados.Modificar)
        SalvarValores();

      return;
    }
  }

  menuSelecionado = menuSelecionado + 1;

  if (menuSelecionado > 2)
    menuSelecionado = 0;

}

void GerarMenu(struct DadosMenu dados)
{
  strcpy(linhasDisplay.Linhas[0], dados.Titulo);
  strcpy(linhasDisplay.Linhas[1], "--------------");

  String tempString;
  char tempChar[14];

  for (int i = 0; i < 4; i++)
  {
    tempString = selecionarItem(dados.NomeDados[i], dados.Dados[i],
                                dados.Posicao == i + 1, dados.Modificar, dados.MenuDeConfiguracao);

    tempString.toCharArray(tempChar, 14);

    strcpy(linhasDisplay.Linhas[i + 2], tempChar);
  }
}

String  selecionarItem(String item, int valor, bool selecionado, bool modificar, bool menuDeConfiguracao)
{
  if (item == "")
    return "";

  if (!menuDeConfiguracao)
  {
    return "  " + item + " " + valor;
  }

  if (selecionado)
  {
    if (modificar)
    {
      return ">>" + item + " " + valor;
    }
    return "> " + item + " " + valor;
  }

  return "  " + item + " " + valor;
}

void SalvarValores()
{
  tempoDesejado = (dadosMenuConfiguracao.Dados[0] * 60) + dadosMenuConfiguracao.Dados[1];
  temperaturaDesejada = dadosMenuConfiguracao.Dados[2];
  luzDisplay = dadosMenuConfiguracao.Dados[3];

  EEPROM.update(0, luzDisplay);
  EEPROMWriteInt(2, tempoDesejado);
  EEPROMWriteInt(4, temperaturaDesejada);
  

  //LuzDisplay(luzDisplay);
}

void CarregarValoresEeprom()
{
  luzDisplay = EEPROM.read(0);
  tempoDesejado = EEPROMReadInt(2);
  temperaturaDesejada = EEPROMReadInt(4);

  dadosMenuConfiguracao.Dados[0] = tempoDesejado / 60;
  dadosMenuConfiguracao.Dados[1] = tempoDesejado - (dadosMenuConfiguracao.Dados[0] * 60);
  dadosMenuConfiguracao.Dados[2] = temperaturaDesejada;
  dadosMenuConfiguracao.Dados[3] = luzDisplay;
}


void EEPROMWriteInt(int address, int value)
{
  byte two = (value & 0xFF);
  byte one = ((value >> 8) & 0xFF);
  
  EEPROM.update(address, two);
  EEPROM.update(address + 1, one);
}
 
int EEPROMReadInt(int address)
{
  long two = EEPROM.read(address);
  long one = EEPROM.read(address + 1);
 
  return ((two << 0) & 0xFFFFFF) + ((one << 8) & 0xFFFFFFFF);
}
