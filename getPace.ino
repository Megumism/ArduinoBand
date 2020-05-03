#include "getThing.h"
void getThing::getPace()
{
    //输入节拍，节拍格式：120#，以#结尾
    lcd.begin(16, 2);
    lcd.print("Rhythm:");
    lcd.setCursor(0, 1);
    lcd.blink();
    key = 0;
    Rhythm = 0;

    //一直记录数据，直到输入终止符#
    while (key != '#')
    {
        key = keyboard.getKey();

        //检测到按键输入
        if ((key != 0) && (key != '#'))
        {
            //修正7，8，9输入
            if ((key >= 'E') && (key <= 'G'))
            {
                key = key - 14;
            }
            lcd.print(key);
            Rhythm = 10 * Rhythm + (key - '0');
        }
    }
}