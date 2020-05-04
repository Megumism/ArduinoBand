#include "getThing.h"
#include "string.h"

void getThing::getTone()
{ 
char Toneflag = 'C'; // Toneflag:A-G
int letter = 0; // 0 means C, 1 means D

    lcd.begin(16, 2);
    lcd.print("Tone:");
    lcd.setCursor(1, 1);
    lcd.print("C");
    key = 0;
    
    while (key != 'D')
    {
        key = keyboard.getKey();
        
        if (key != 0)
        {
            if (key == '*') // b flat
            {
                lcd.setCursor(0,1); lcd.print('b');
                Tone--;
            }
            if (key == '#') // # sharp
            {
                lcd.setCursor(0,1); lcd.print('#');
                Tone++;
            }
            if (key == 'B') // Up
            {
                letter++; Toneflag++;
                lcd.setCursor(1,1); lcd.print(Toneflag);
            }
            if (key == 'C') // Down
            {
                letter--; Toneflag--;
                lcd.setCursor(1,1); lcd.print(Toneflag);
            }
        }   
    }
    Tone += TONE2[letter + 2];
}
