#include "getThing.h"
void getThing::getPace()
{
    //������ģ����ĸ�ʽ��120#����#��β
    lcd.begin(16, 2);
    lcd.print("Rhythm:");
    lcd.setCursor(0, 1);
    lcd.blink();
    key = 0;
    Rhythm = 0;

    //һֱ��¼���ݣ�ֱ��������ֹ��#
    while (key != '#')
    {
        key = keyboard.getKey();

        //��⵽��������
        if ((key != 0) && (key != '#'))
        {
            //����7��8��9����
            if ((key >= 'E') && (key <= 'G'))
            {
                key = key - 14;
            }
            lcd.print(key);
            Rhythm = 10 * Rhythm + (key - '0');
        }
    }
}