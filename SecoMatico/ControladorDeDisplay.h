#include <PCD8544.h>

struct LinhasDisplay
{
  char Linhas[6][14];
};

static PCD8544 Lcd;

struct LinhasDisplay LinhasDisplayMemoria;

void MostrarDisplay(struct LinhasDisplay linhasDisplay)
{

  for (int i = 0; i < 6; i++)
  {
    if (linhasDisplay.Linhas[i] != LinhasDisplayMemoria.Linhas[i])
    {
      Lcd.setCursor(0, i);
      Lcd.print("              ");
      Lcd.setCursor(0, i);
      Lcd.print(linhasDisplay.Linhas[i]);
    }
  }

  LinhasDisplayMemoria = linhasDisplay;
}


void InicializarDisplay()
{
  Lcd.begin(84, 48);
}


void LimparDisplay()
{
  for (int i = 0; i < 6; i++)
  {
    Lcd.setCursor(0, i);
    Lcd.print("              ");
  }
}

void DesligarDisplay()
{
  Lcd.clear();  
}