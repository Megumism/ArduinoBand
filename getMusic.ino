#include "getThing.h"

void getThing::getMusic()
{
int note = 0, beat = 0, lr = 0;

    lcd.begin(16, 2);
    lcd.print("Your song:");
    lcd.setCursor(0, 1);
    lcd.print("Note:   Beat:");
    lcd.setCursor(6,1);
    lcd.blink();
    key = 0;
    num = 0;

    while (0 == 0)                //exit when press D twice
    {
        key = 0;
        key = keyboard.getKey();
        
        if (key == 'A')            //backspace
        {
            if (lr != 0)
            {
                beat /= 10;
                lcd.setCursor(13,1);
                lcd.print(" ");
                lcd.setCursor(13,1);
                lcd.blink();
            }
            if (lr == 0)
            {
                note /= 10;
                if (note > 0)
                {
                    lcd.setCursor(7,1);
                    lcd.print(' ');
                    lcd.setCursor(7,1);
                }
                if (note == 0)
                {
                    lcd.setCursor(6,1);
                    lcd.print(' ');
                    lcd.setCursor(6,1);
                }
            }
        }
        if (key == 'B')               //left
        {
            lr--;
            if (note >= 10) lcd.setCursor(8,1);
            if ((note < 10) && (note != 0)) lcd.setCursor(7,1);
            if (note == 0) lcd.setCursor(6,1);
            lcd.blink();
        }
        if (key == 'C')              //right
        {
            lr++;
            if (beat == 0) lcd.setCursor(13,1);
            if (beat != 0) lcd.setCursor(14,1);
            lcd.blink();
        }
        if ((key >= '1') && (key <= '9'))      //number
        {
            if (lr == 0)
            {
                note = 10 * note + (key - '0');
                lcd.setCursor(6,1);
                lcd.print(note);
            }
            if (lr != 0)
            {
                beat = key - '0';
                lcd.print(beat);
            }
        }
        if (key == '*')           //flat
        {
            UpDown[num] = -1;
            lcd.setCursor(5,1);
            lcd.print('b');
            if (note >= 10) lcd.setCursor(8,1);
            if ((note < 10) && (note != 0)) lcd.setCursor(7,1);
            if (note == 0) lcd.setCursor(6,1);
            lcd.blink();
        }
        if (key == '#')           //sharp
        {
            UpDown[num] = 1;
            lcd.setCursor(5,1);
            lcd.print('#');
            if (note >= 10) lcd.setCursor(8,1);
            if ((note < 10) && (note != 0)) lcd.setCursor(7,1);
            if (note == 0) lcd.setCursor(6,1);
            lcd.blink();
        }
        if (key == 'D')           //enter
        {
            if (beat != 0) 
            {
                if (note != 0) Note[num] = Tone + 12 * (note / 10) + TONE[(note % 10) - 1] + UpDown[num]; 
                RealNote[num] = note % 10;
                Dura[num] = beat;
                
                num++;
                note = 0;
                beat = 0;
                lr = 0;
                
                lcd.begin(16, 2);
                lcd.print("Your song:");
                lcd.setCursor(0, 1);
                lcd.print("Note:   Beat:");
                lcd.setCursor(6,1);
                lcd.blink();
            }
            else break;         //press D twice and break
        }
    }
}
