#include "Display.h"
void Display::Amazing()
{
    //屏幕显示“Amazing!|Back to menu..”数秒后，回到开始界面
    lcd.begin(16, 2);
    lcd.print("    Amazing!");
    lcd.setCursor(0, 1);
    lcd.print(" Back to menu..");
    delay(2000);
}