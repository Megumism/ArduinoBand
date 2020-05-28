#include "MusicGame.h"

void MusicGame::play(LiquidCrystal lcd, keyboard44 keyboard, Buzzer buzzer, int Note[], int main, int BPM)
{
    long int startTime = millis();
    float noteTime = 60000.0 / BPM; //单个音节持续的毫秒数
    int paceCount = 0;
    int noteCount = 0;
    int timeCount = 0;
    bool buzzerOn = false;
    char buffer[17];
    srand(millis());

    for (int i = 0; i < 17; i++)
    {
        buffer[i] = ' ';
    }

    while (Note[noteCount] != 11111)
    {
        if (!buzzerOn)
        {
            buzzerOn = true;
            paceCount += abs(Note[noteCount]) / 1000;
            tone(buzzer.buzzerPin, buzzer.ToneX(main, Note[noteCount]));
            noteCount++;
        }
        else if (millis() - startTime >= noteTime * paceCount)
        {
            buzzerOn = false;
            noTone(buzzer.buzzerPin);
        }
        if (millis() - startTime >= noteTime * timeCount){
            timeCount++;
            for (int i = 0; i < 16; i++)
            {
                buffer[i] = buffer[i + 1];
            }
            if (rand() > 0.5 * RAND_MAX)
            {
                buffer[16] = '-';
            }
            else
                buffer[16] = ' ';

            lcd.begin(16, 2);
            lcd.println(buffer);
        }
    }
    noTone(buzzer.buzzerPin);
};