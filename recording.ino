#include "Display.h"
void Display::recording()
{
    //œ‘ æ∆¡∂Ã‘›œ‘ æ°∞Recording°≠°±
    lcd.begin(16, 2);
    lcd.print("  Recording...");
    delay(2000);
}
