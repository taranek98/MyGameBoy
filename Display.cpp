#include "Display.h"
#include "Pins.h"
#include <Arduino.h>
//#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_HX8357.h"
#include "string"
#include "Cartridge.h"
#include <string>

static Adafruit_HX8357 Display = Adafruit_HX8357(DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN);
static Cursor Display_Cursor = {0,0};

void Display_Init()
{
    Display.begin();
    Display.fillScreen(HX8357_BLACK);
    Display.setRotation(1);
    Display.setTextColor(HX8357_WHITE);
    Display.setTextSize(10);
    Display.setCursor(140, 110);
    Display.println("LUCY");
    Display.setTextSize(3);
    Display.setCursor(115, 220);
    Display.println("GameBoy Emulator");
    delay(DISPLAY_TITLE_SHOW_DELEY);
}

void Display_PrintError(char * error_name)
{
    Display.fillScreen(HX8357_BLACK);
    Display.setCursor(5,5);
    Display.setTextSize(2);
    Display.println(error_name);
}
static void Display_ClearScreen()
{
    Display.fillScreen(HX8357_BLACK);
    Display.setCursor(0,0);
}

static void Display_DrawSelector(int x, int y)
{
    Display.drawLine(x,y, x+40,y, HX8357_WHITE);                            //pozioma kreska
    Display.drawLine(x,y, x+15,y-10, HX8357_WHITE);                         //kreska w gore
    Display.drawLine(x,y, x+15,y+10, HX8357_WHITE);                         //kreska w dol
}

static void Display_RubberSelector(int x, int y)
{
    Display.drawLine(x,y, x+40,y, HX8357_BLACK);                            //pozioma kreska
    Display.drawLine(x,y, x+15,y-10, HX8357_BLACK);                         //kreska w gore
    Display.drawLine(x,y, x+15,y+10, HX8357_BLACK);                         //kreska w dol
}

void Display_PrintNumber(int number)
{
    Display.print(number);
}

void Display_StartRomMenu()
{
    Display_ClearScreen();
    Display_Cursor.x = DISPLAY_START_ROM_MENU_X;
    Display_Cursor.y = DISPLAY_START_ROM_MENU_Y;
}

void Display_AddRomName(char * romName)
{
    Display.println(romName);
}

void Display_StartSelector()
{
    Display_DrawSelector(Display_Cursor.x, Display_Cursor.y);
}

void Display_SelectorDown()
{
    Display_RubberSelector(Display_Cursor.x, Display_Cursor.y);
    Display_Cursor.y += DISPLAY_SELECTOR_DISTANCE_Y;
    Display_DrawSelector(Display_Cursor.x, Display_Cursor.y);     
    delay(DISPLAY_BOUNCE_DELEY);  
}

void Display_SelectorUp()
{
    Display_RubberSelector(Display_Cursor.x, Display_Cursor.y);
    Display_Cursor.y -= DISPLAY_SELECTOR_DISTANCE_Y;
    Display_DrawSelector(Display_Cursor.x, Display_Cursor.y);     
    delay(DISPLAY_BOUNCE_DELEY);  
}

void Display_PrintRomInfo()
{
    Cartridge * cartridgePointer = Cartridge_GetPointer();
    
    Display_ClearScreen();
    Display.println("Wczytany ROM");
    
    Display.print("Title: \t");
    Display.print(cartridgePointer->header->Title);
    Display.print("\n");

    Display.print("Type: \t");
    Display.print(cartridgePointer->header->CartridgeType);
    Display.print(" (");
    Display.print(Cartridge_GetTypeName());
    Display.print(")\n");

    Display.print("ROM Size: \t");
    Display.print(cartridgePointer->header->ROM_Size);
    Display.print("\n");
    
    Display.print("RAM Size: \t");
    Display.print(cartridgePointer->header->RAM_Size);
    Display.print("\n");
    
    Display.print("Licensee Code: \t");
    Display.print(cartridgePointer->header->NewLicenseeCode);
    Display.print(" (");
    Display.print(Cartridge_GetTypeName());
    Display.print(")\n");

    Display.print("ROM Version: \t");
    Display.print(cartridgePointer->header->Version);
}