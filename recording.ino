#include "Display.h"
void Display::recording()
{
    //��ʾ��������ʾ��Recording����
    lcd.begin(16, 2);
    lcd.print("  Recording...");
    delay(2000);
}
