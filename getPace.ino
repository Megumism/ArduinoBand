#include "getThing.h"

void getThing::getPace()
{
  
    //get BPM: beat per minute
    lcd.begin(16, 2);
    lcd.print("BPM:");
    lcd.setCursor(0, 1);
    lcd.blink();
    key = 0;
    while (key != 'D') // input end with D
    {
        key = keyboard.getKey();
        if ((key != 0) && (key != 'D') && (key != 'A')) // normal output
        {
            lcd.print(key);
            Rhythm = 10 * Rhythm + (key - '0');
        }
        if (key == 'A') // backspace
        {
            Rhythm /= 10;
            lcd.clear();
            lcd.print("BPM:");
            lcd.setCursor(0, 1);
            if (Rhythm != 0) lcd.print(Rhythm);
            lcd.blink();
        }
    }
    
    //get Metre: 3/4, 9/8
    int lr = 0; // left or right ,0 means left, 1 means right
    lcd.begin(16, 2);
    lcd.print("Metre:");
    lcd.setCursor(1, 1);
    lcd.print('/');
    lcd.setCursor(2 * lr, 1);
    lcd.blink();
    key = 0;
    while (key != 'D')
    {
        key =  keyboard.getKey();
        if ((key != 0) && (key != 'D'))
        {
            if (key == 'B') lr--;
            if (key == 'C') lr++;
            if ((key >= '1') && (key <= '9')) 
            {
                lcd.print(key);
                if (lr == 0) metre = key - '0';
            }
            lcd.setCursor(2 * lr, 1);
            lcd.blink();
        }
    }
}
