#include "MusicGame.h"

void MusicGame::play(LiquidCrystal lcd, keyboard44 keyboard, Buzzer buzzer, int Note[], int length, int main, int BPM)
{
    long int startTime = millis();
    float noteTime = 60000.0 / BPM; //单个音节持续的毫秒数
    int paceCount = 0;
    int noteCount = 0;
    int timeCount = 0;
    bool buzzerOn = false;
    char buffer[17];

    while (Note[noteCount] != 11111)
    {
        if (!buzzerOn)
        {
            buzzerOn = true;
            paceCount += abs(Note[noteCount]) / 1000;
            if (Note[noteCount] % 1000 != 0)
            {
                tone(buzzer.buzzerPin, buzzer.ToneX(main, Note[noteCount]));
            }
            else
            {
                noTone(buzzer.buzzerPin);
            }
            noteCount++;
        }
        else if (millis() - startTime >= noteTime * paceCount)
        {
            buzzerOn = false;
            noTone(buzzer.buzzerPin);
        }
        if (millis() - startTime >= 1000 * timeCount)
        {
            lcd.begin(16, 2);
            lcd.print("      Playing...");
            lcd.setCursor(0, 0);
            lcd.print(timeCount);
            lcd.print("s");
            lcd.setCursor(0, 1);
            for (int i = 0; i < 16; i++)
            {
                if (i < 16.0 * noteCount / length)
                    lcd.print("=");
                else
                    lcd.print("-");
            }
            timeCount++;
        }
    }
    delay(abs(Note[noteCount - 1]) / 1000 * noteTime);
    noTone(buzzer.buzzerPin);
};