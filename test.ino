//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Music.h"
#include "Score.h"
#include "MyBuzzer.h"

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);
char key; //keyboard input

// LCD pin
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

Buzzer buzzer(2);

//get information
Music music;

Score score;

void setup()
{
    //welcome
    lcd.begin(16, 2);
    Serial.begin(9600);
}

//交互实现
void loop()
{
    int i;
    for (i = 0; i < 50; i++)
    {
        char temp;
        temp = score.writeNote(lcd, keyboard, i);
        if (temp == '-')
            i--;
        if (temp == 'D')
            break;
        if (temp == '0')
            continue;
        buzzer.Sing(C,score.note[i],score.pace[i]);
    }
    buzzer.Sing(C, score.note, score.pace, i);
}
