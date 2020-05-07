#include "Music.h"

void Music::getMusic(LiquidCrystal lcd, keyboard44 keyboard)
{
    songExisitence = true;
}

void Music::getPace(LiquidCrystal lcd, keyboard44 keyboard)
{
    char key = 0;
    //get BPM: beat per minute
    lcd.begin(16, 2);
    lcd.print("BPM:");
    lcd.setCursor(0, 1);
    lcd.blink();
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
            if (Rhythm != 0)
                lcd.print(Rhythm);
            lcd.blink();
        }
    }
}

void Music::getMetre(LiquidCrystal lcd, keyboard44 keyboard) //3/4, 9/8
{
    char key = 0;
    bool lr = false; // left or right ,false means left, true means right

    lcd.begin(16, 2);
    lcd.print("Metre:");
    lcd.setCursor(1, 1);
    lcd.print('/');
    lcd.setCursor(2 * lr, 1);
    lcd.blink();
    while (key != 'D')
    {
        key = keyboard.getKey();
        if ((key != 0) && (key != 'D'))
        {
            if (key == 'B' && lr)
                lr = false;
            if (key == 'C' && !lr)
                lr = true;
            if ((key >= '1') && (key <= '9'))
            {
                lcd.print(key);
                if (!lr) //在左边则赋值
                {
                    metre = key - '0';
                    lr = true; //自动跳转
                }
                else
                {
                    key = 'D'; //自动跳转*2 当然这个比较弱智
                }
            }
            lcd.setCursor(2 * lr, 1);
            lcd.blink();
        }
    }
}

void Music::getTone(LiquidCrystal lcd, keyboard44 keyboard)
{
    char Toneflag = 'C'; // Toneflag:A-G
    int letter = 0;      // 0 means C, 1 means D
    char key = 0;

    lcd.begin(16, 2);
    lcd.print("Tone:");
    lcd.setCursor(0, 1);
    lcd.write(B01111111); //←
    lcd.print(" C ");
    lcd.write(B01111110); //→

    while (key != 'D')
    {
        key = keyboard.getKey();

        if (key != 0)
        {
            if (key == '*') // b flat
            {
                lcd.setCursor(1, 1);
                lcd.print('b');
                Tone--;
            }
            if (key == '#') // # sharp
            {
                lcd.setCursor(1, 1);
                lcd.print('#');
                Tone++;
            }
            if (key == 'B') // Up
            {
                letter++;
                Toneflag++;
                lcd.setCursor(2, 1);
                lcd.print(Toneflag);
            }
            if (key == 'C') // Down
            {
                letter--;
                Toneflag--;
                lcd.setCursor(2, 1);
                lcd.print(Toneflag);
            }
        }
    }
    Tone += TONE2[letter + 2];
}

void Music::Initialize()
{
    memset(UpDown, 0, sizeof(UpDown));
    memset(Note, 0, sizeof(Note));
    memset(Dura, 0, sizeof(Dura));
    memset(RealNote, 0, sizeof(RealNote));
    Tone = 0;
    Rhythm = 0;
    metre = 0;
    num = 0;
    pinX = 0;
    songExisitence = false;
}
