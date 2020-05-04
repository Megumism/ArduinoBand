#include "Display.h"

void Display::music()
{
float Frequency, Duration, xx;
int sum = 0;

    lcd.begin(16, 2);
    lcd.setCursor(0,0);

    for (int i = 0; i < num; i++)
    {
        if (UpDown[i] == 1) lcd.print('#');
        if (UpDown[i] == -1) lcd.print('b');
        
        lcd.print(RealNote[i]);
        
        xx = Dura[i];          //change the type from int to float
        sum += Dura[i];
        Duration = xx / Rhythm * 60 * 1000;
        Frequency = C3 * pow(1.059463, Note[i]);
        tone(Buzzer, Frequency, Duration);
        delay(Duration / xx);
        
        for (int j = 0; j <= Dura[i] - 2; j++)
        {
            lcd.print('-');
            delay(Duration / xx);
        }
        lcd.print(" ");

        if (sum % metre == 0) //一个小节的末尾
        {
            pinX++; //小节数++
            pin[pinX] = i + 1; //记录每一个小节开头音符对应的序号
            if (sum/metre == 1) //第一个小节末尾，直接输出光标下移
            {
                lcd.print('|');
                lcd.setCursor(0,1);
            }
            else //其余小节末尾，作翻页操作
            {
                lcd.clear();
                lcd.begin(16,2);
                for (int j = pin[pinX - 1]; j <= i; j++)
                {
                    lcd.print(RealNote[j]);
                    for (int k = 0; k <= Dura[j] - 2; k++) lcd.print('-');
                    lcd.print(" ");
                }
                lcd.print('|');
                lcd.setCursor(0,1);                  
            }
        }
    }
    pin[num + 1] = num;
}
