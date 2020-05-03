#include "getThing.h"
void getThing::getTone()
{ 
char UDflag = ' ', Toneflag = 'C'; //UDflag:whether use */# or not; Toneflag:A-G
int letter = 0; //0 means C, 1 means D
int TONE2[7] = {9, 11, 0, 2, 4, 5, 7}; //a new TONE for ABCDEFG

    lcd.begin(16, 2);
    lcd.print("Tone:");
    lcd.setCursor(0, 1);
    lcd.print(" C");
    key = 0;
    Tone = 0;
    
    while (key != 'D')
    {
        key = keyboard.getKey();
        
        if (key != 0)
        {
            if (key == '*') // b flat
            {
                UDflag = 'b'; Tone--;
            }
            if (key == '#') // # sharp
            {
                UDflag = key; Tone++;
            }
            if (key == 'B') // Up
            {
                letter++; Toneflag++;
            }
            if (key == 'C') // Down
            {
                letter--; Toneflag--;
            }
            //Display
            lcd.begin(16, 2);
            lcd.print("Tone:");
            lcd.setCursor(0, 1);
            lcd.print(UDflag);
            lcd.print(Toneflag);
        }   
    }
    Tone += TONE2[letter + 2];
    Serial.println(Tone);
}
