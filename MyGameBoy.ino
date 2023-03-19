#include "Display.h"
#include "Cartridge.h"
#include "Button.h"

void setup() 
{  
  Display_Init();
  Button_Init();
  Cartridge_RomLoad();
}

void loop() 
{
  // put your main code here, to run repeatedly
}
