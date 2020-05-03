#include "Display.h"
void Display::welcome()
{
    //欢迎语句
    lcd.begin(16, 2); //设置列行值
    lcd.print("   Welcome to");
    lcd.setCursor(0, 1); //光标跳转到下一行
    lcd.print("  Garbage Band");
    delay(2000);
}
