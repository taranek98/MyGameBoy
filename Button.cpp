#include "Button.h"
#include <Arduino.h>
#include "Pins.h"

bool volatile Button_DownIsClick = false;
bool volatile Button_UpIsClick = false;
bool volatile Button_SelectIsClick = false;

static void Button_DownHandler()
{
    Button_DownIsClick = !Button_DownIsClick;

}
static void Button_UpHandler()
{
    Button_UpIsClick = !Button_UpIsClick;
}

static void Button_SelectHandler()
{
    Button_SelectIsClick = !Button_SelectIsClick;
}


void Button_Init()
{
    /*Set Pins Buttons*/
    pinMode(BUTTON_DOWN_PIN, INPUT);
    pinMode(BUTTON_UP_PIN, INPUT);
    pinMode(BUTTON_SELECT_PIN, INPUT);

    /*Set Button Handler*/
    attachInterrupt(digitalPinToInterrupt(BUTTON_DOWN_PIN), Button_DownHandler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON_UP_PIN), Button_UpHandler, CHANGE);
    attachInterrupt(digitalPinToInterrupt(BUTTON_SELECT_PIN), Button_SelectHandler, CHANGE);
}

bool Button_IsDownClick()
{
    return Button_IsDownClick;
}

bool Button_IsUpClick()
{
    return Button_IsUpClick;
}

bool Button_IsSelectClick()
{
    return Button_IsSelectClick;
}
