#include "GetThing.h"

void GetThing::getMusic(LiquidCrystal lcd, keyboard44 keyboard)
{
    int note = 0, beat = 0, lr = 0;
    char key = 0;

    lcd.begin(16, 2);
    lcd.print("Your song:");
    lcd.setCursor(0, 1);
    lcd.print("Note:   Beat:");
    lcd.setCursor(6, 1);
    lcd.blink();
    num = 0;

    while (0 == 0) //exit when press D twice
    {
        key = 0;
        key = keyboard.getKey();

        if (key == 'A') //backspace
        {
            if (lr != 0)
            {
                beat /= 10;
                lcd.setCursor(13, 1);
                lcd.print(" ");
                lcd.setCursor(13, 1);
                lcd.blink();
            }
            if (lr == 0)
            {
                note /= 10;
                if (note > 0)
                {
                    lcd.setCursor(7, 1);
                    lcd.print(' ');
                    lcd.setCursor(7, 1);
                }
                if (note == 0)
                {
                    lcd.setCursor(6, 1);
                    lcd.print(' ');
                    lcd.setCursor(6, 1);
                }
            }
        }
        if (key == 'B') //left
        {
            lr--;
            if (note >= 10)
                lcd.setCursor(8, 1);
            if ((note < 10) && (note != 0))
                lcd.setCursor(7, 1);
            if (note == 0)
                lcd.setCursor(6, 1);
            lcd.blink();
        }
        if (key == 'C') //right
        {
            lr++;
            if (beat == 0)
                lcd.setCursor(13, 1);
            if (beat != 0)
                lcd.setCursor(14, 1);
            lcd.blink();
        }
        if ((key >= '1') && (key <= '9')) //number
        {
            if (lr == 0)
            {
                note = 10 * note + (key - '0');
                lcd.setCursor(6, 1);
                lcd.print(note);
            }
            if (lr != 0)
            {
                beat = key - '0';
                lcd.print(beat);
            }
        }
        if (key == '*') //flat
        {
            UpDown[num] = -1;
            lcd.setCursor(5, 1);
            lcd.print('b');
            if (note >= 10)
                lcd.setCursor(8, 1);
            if ((note < 10) && (note != 0))
                lcd.setCursor(7, 1);
            if (note == 0)
                lcd.setCursor(6, 1);
            lcd.blink();
        }
        if (key == '#') //sharp
        {
            UpDown[num] = 1;
            lcd.setCursor(5, 1);
            lcd.print('#');
            if (note >= 10)
                lcd.setCursor(8, 1);
            if ((note < 10) && (note != 0))
                lcd.setCursor(7, 1);
            if (note == 0)
                lcd.setCursor(6, 1);
            lcd.blink();
        }
        if (key == 'D') //enter
        {
            if (beat != 0)
            {
                if (note != 0)
                    Note[num] = Tone + 12 * (note / 10) + TONE[(note % 10) - 1] + UpDown[num];
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
                lcd.setCursor(6, 1);
                lcd.blink();
            }
            else
                break; //press D twice and break
        }
    }
    songExisitence = true;
}

void GetThing::getPace(LiquidCrystal lcd, keyboard44 keyboard)
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

void GetThing::getMetre(LiquidCrystal lcd, keyboard44 keyboard)//3/4, 9/8
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
                if (lr == 0)
                    metre = key - '0';
            }
            lcd.setCursor(2 * lr, 1);
            lcd.blink();
        }
    }
}

void GetThing::getTone(LiquidCrystal lcd, keyboard44 keyboard)
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

void GetThing::Initialize()
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
