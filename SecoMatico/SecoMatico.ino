#define USE_TIMER_2 true
#define TIMER_INTERVAL_MS 500

#include "TimerInterrupt.h"

/*
  Controle de Tempratura com Fluxo De Ar em um Secador de Café a Lenha
*/

bool flagLed = false;

void TimerHandler(void)
{
  if(flagLed)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    flagLed = false;
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
    flagLed = true;
  }
}

// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

ITimer2.init();

if (ITimer2.attachInterruptInterval(TIMER_INTERVAL_MS, TimerHandler));

}

// the loop function runs over and over again forever
void loop() 
{

}
