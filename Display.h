#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_START_ROM_MENU_X 150
#define DISPLAY_START_ROM_MENU_Y 10
#define DISPLAY_BOUNCE_DELEY 500
#define DISPLAY_TITLE_SHOW_DELEY 500
#define DISPLAY_SELECTOR_DISTANCE_Y 25

typedef struct 
{
    unsigned short x;
    unsigned short y;
}Cursor;



void Display_Init();
void Display_PrintError(char * error_name);
void Display_PrintRomName(char * rom_name);
void Display_StartSelector();
void Display_PrintNumber(int number);
void Display_StartRomMenu();
void Display_AddRomName(char * romName);
void Display_SelectorDown();
void Display_SelectorUp();
void Display_PrintRomInfo();


#endif