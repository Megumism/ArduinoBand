#include "Display.h"
void Display::Amazing()
{
    //��Ļ��ʾ��Amazing!|Back to menu..������󣬻ص���ʼ����
    lcd.begin(16, 2);
    lcd.print("    Amazing!");
    lcd.setCursor(0, 1);
    lcd.print(" Back to menu..");
    delay(2000);
}