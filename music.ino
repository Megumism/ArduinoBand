#include "Display.h"
//中央C
float C3 = 261.63;
void Display::music()
{
    /*�Ÿ裬��ʽΪ
      b7--- 6- 2- 4---
      ���������ֹ���
    */
    lcd.begin(16, 2);
    lcd.print("Enjoy Your song!");
    lcd.setCursor(0, 1);
    for (int i = 0; i < num; i++)
    {

        //���������
        if (UpDown[i] == 1)
        {
            lcd.print('#');
        }
        if (UpDown[i] == -1)
        {
            lcd.print('b');
        }

        //����������
        xx = Dura[i]; //��������ת��
        sum += Dura[i];
        Duration = xx / Rhythm * 60 * 1000;
        Frequency = C3 * pow(1.059463, Note[i]);
        tone(Buzzer, Frequency, Duration);

        //�������1-7
        lcd.print(RealNote[i]);
        if (sum >= 4)
        {
            lcd.scrollDisplayLeft();
        } //�����һ��

        //�������
        delay(Duration / xx);
        for (int j = 0; j <= Dura[i] - 2; j++)
        {
            lcd.print('-');
            delay(Duration / xx);
            if (sum >= 12)
            {
                lcd.scrollDisplayLeft();
            } //���������
        }

        lcd.print(" "); //����֮��ķָ�
    }
}
