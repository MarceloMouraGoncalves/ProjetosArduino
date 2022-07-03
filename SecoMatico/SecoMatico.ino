#include "LeitorDeTemperatura.h"
#include "ControladorDeEstados.h"
#include "ControladorDePosicao.h"
#include "ControladorDeTemperatura.h"
#include "ControladorDeMenus.h"
#include "ControladorDeIndicadores.h"

/*
  Controle de Tempratura com Fluxo De Ar em um Secador de Café a Lenha
*/

unsigned int tempoAnteriorMs = 0;        
unsigned int tempoAtualMs = 0;

float Temperatura = 0;
float TemperaturaDesejada = 0;
float ControleDeAngulo = 0;
unsigned long int Tempo = 0;

unsigned long int ContadorLoopControlePosicao = 0;
unsigned long int ContadorLoopControleTemperatura = 0;

bool Motor1Inicializacao;
bool Motor2Inicializacao;

// the setup function runs once when you press reset or power the board
void setup() 
{  
  Serial.begin(115200);

  InicializarControleDeMenu();
  InicializarControladorDeIndicadores();
  InicializarLeituraDeTemperatura();
  InicializarControladorDeEstados();  
  InicializarControleDePosicao(LOOP_INTERVALO_MS * LOOP_CONTROLE_POSICAO, &Motor1Inicializacao, &Motor2Inicializacao);
  InicializarControleDeTemparatura(LOOP_INTERVALO_MS * LOOP_CONTROLE_TEMPERATURA, DadosMenuControlePid.Valores[0], DadosMenuControlePid.Valores[1], DadosMenuControlePid.Valores[2]);
}

// the loop function runs over and over again forever
void loop() 
{
  tempoAtualMs = millis();

  if (tempoAtualMs - tempoAnteriorMs < LOOP_INTERVALO_MS) 
  {
    return;
  }
  
  tempoAnteriorMs = tempoAtualMs;
  Tempo += tempoAtualMs;

  AtualizarMenu();

  ContadorLoopControlePosicao++;
  ContadorLoopControleTemperatura++;

  switch (DefinirEstadoAtual(ContadorLoopControlePosicao, ContadorLoopControleTemperatura, Temperatura, DadosMenuControlePid.Valores[3], InicializacoDeMotoresCompleta()))
  {
    case EstadoControleManual:
      IniciarControleManual();
      break;

    case EstadoEmergenciaDeTemperatura:
      EmergenciaTemperaturaMax();
      break;

    case EstadoInicializacaoDePosicao:
      InicializarPosicao();
      break;

    case EstadoControleDePosicao:
      ContadorLoopControlePosicao = 0;
      ControleDePosicao();
      break;
    
    case EstadoControleDeTemparatura:
      ContadorLoopControleTemperatura = 0;      
      ControleDeTemparatura();
      break;

    default:
      break;
  }
}

void AtualizarTemperatura()
{
  Temperatura = LerTemperaturaC();
  TemperaturaDesejada = DadosMenuTemperatura.Valores[0];
}

void IniciarControleManual()
{
  PararRotacao();
  AtivarIndicadorEmergencia();
  strcpy(DadosMenuSupervisao.NomeDados[0], "Ctrl. Manual!");
}

void EmergenciaTemperaturaMax()
{
  ForcarPosicaoMax();
  AtivarIndicadorEmergencia();
  AtualizarTemperatura();

  strcpy(DadosMenuSupervisao.NomeDados[0], "Emergencia!");
}

void InicializarPosicao()
{
  InicializarPosicaoMin(&Motor1Inicializacao, &Motor2Inicializacao);
  AtivarIndicadorAlarm();
  AtualizarTemperatura();
  
  strcpy(DadosMenuSupervisao.NomeDados[0], "Inicializacao");
  AtualizarDados();
}

void ImprimirStatus()
{
  Serial.print(ContadorLoopControleTemperatura);
  Serial.print(" Aquisicao Temperatura = ");  
  Serial.println(Temperatura);
}

void ControleDePosicao()
{
  AtivarIndicadorBom();
  AtualizarTemperatura();

  ControlarPosicao();

  strcpy(DadosMenuSupervisao.NomeDados[0], "Ctrl. Posicao");
  AtualizarDados();

  ImprimirStatus();
}

void ControleDeTemparatura()
{
  AtivarIndicadorBom(); 

  AtualizarTemperatura();
  
  ControleDeAngulo = CalcularControle(Temperatura, TemperaturaDesejada);
  AjustarAlteracaoDeAngulo(&ControleDeAngulo);

  strcpy(DadosMenuSupervisao.NomeDados[0], "Ctrl. Temp.");
  AtualizarDados();   
}

void AtualizarDados()
{
  DadosMenuSupervisao.Valores[1] = Temperatura;
  DadosMenuSupervisao.Valores[2] = TemperaturaDesejada;
  DadosMenuSupervisao.Valores[3] = ControleDeAngulo;
}