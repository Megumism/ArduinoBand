#include "Display.h"

void Display::score()
{
int head = 0;
    lcd.begin(16,2);
    key = 0;
    
    for (int i = 0; i < pin[1]; i++)
    {
        lcd.print(RealNote[i]);
        for (int j = 0; j <= Dura[i] - 2; j++) lcd.print('-');
        lcd.print(' ');
    }
    lcd.print('|');
    lcd.setCursor(0,1);
    for (int i = pin[1]; i < pin[2]; i++)
    {
        lcd.print(RealNote[i]);
        for (int j = 0; j <= Dura[i] - 2; j++) lcd.print('-');
        lcd.print(' ');
    }
    lcd.print('|');
    
    while (key != 'D')
    {
        key = keyboard.getKey();
        if (key == 'B') head--;
        if (key == 'C') head++;
        if (key != 0)    //prevent non-stop refresh
        {
            lcd.clear();
            lcd.setCursor(0,0);
            for (int i = pin[head]; i < pin[head + 1]; i++)
            {
                lcd.print(RealNote[i]);
                for (int j = 0; j <= Dura[i] - 2; j++) lcd.print('-');
                lcd.print(' ');
            }
            lcd.print('|');  
            lcd.setCursor(0,1);
            for (int i = pin[head + 1]; i < pin[head + 2]; i++)
            {
                lcd.print(RealNote[i]);
                for (int j = 0; j <= Dura[i] - 2; j++) lcd.print('-');
                lcd.print(' ');
            }
            lcd.print('|');      
        }
    }
}
