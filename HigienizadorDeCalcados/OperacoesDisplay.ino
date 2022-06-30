
static PCD8544 lcd;

struct LinhasDisplay LinhasDisplayMemoria;


void MostrarDisplay(struct LinhasDisplay linhasDisplay)
{

  for (int i = 0; i < 6; i++)
  {
    if (linhasDisplay.Linhas[i] != LinhasDisplayMemoria.Linhas[i])
    {
      lcd.setCursor(0, i);
      lcd.print("              ");
      lcd.setCursor(0, i);
      lcd.print(linhasDisplay.Linhas[i]);
    }
  }

  LinhasDisplayMemoria = linhasDisplay;
}


void IniciarDisplay()
{
  lcd.begin(84, 48);
}


void LimparDisplay()
{
  for (int i = 0; i < 6; i++)
  {
    lcd.setCursor(0, i);
    lcd.print("              ");
  }
}

void LuzDisplay(int valor)
{
  int luz;

  luz = map(valor, 0, 100, 0, 254);

//  analogWrite(DISPLAY_LUZ_PIN, luz);

}

void DesligarDisplay()
{
  //LuzDisplay(0);
  lcd.clear();  
}
