#include "MyBuzzer.h"

void Buzzer::Sing(int Main, int Song[], char beat[], int length)
{
    int sing;
    for (int i = 0; i < length; i++)
    {
        Serial.print("Song[");
        Serial.print(i);
        Serial.print("]=");
        Serial.println(Song[i]);
        Serial.print("beat[");
        Serial.print(i);
        Serial.print("]=");
        Serial.println(int(beat[i]));

        if (Song[i] != 0)
        {
            tone(buzzerPin, ToneX(Main, Song[i]));
        }
        else
            noTone(buzzerPin);
        delay(int(beat[i]) * 500); //500要改掉的
    }
    noTone(buzzerPin);
}

void Buzzer::Sing(int Main, int Note, char beat)
{
    tone(buzzerPin, ToneX(C, Note), beat*500);
    noTone(buzzerPin);
}

int Buzzer::ToneX(int main, int SoundIN)
{
    char Tone;
    char Height;
    char UpDown;
    int SoundOUT;
    if (SoundIN >= 0)
    {
        Tone = SoundIN % 100 / 10;
        Height = SoundIN / 100;
        UpDown = SoundIN % 10 - 1;
    }
    else
    {
        Tone = (-SoundIN) % 100 / 10;
        Height = -(((-SoundIN) / 100) + 1);
        UpDown = (-SoundIN % 10) - 1;
    }
    // Serial.println(int(Tone));
    // Serial.println(int(Height));
    // Serial.println(int(UpDown));
    if (Tone == 1)
        Tone = 0;
    else if (Tone == 2)
        Tone = 2;
    else if (Tone == 3)
        Tone = 4;
    else if (Tone == 4)
        Tone = 5;
    else if (Tone == 5)
        Tone = 7;
    else if (Tone == 6)
        Tone = 9;
    else if (Tone == 7)
        Tone = 11;
    // Serial.println(SoundOUT);
    return int(pow(2, (main + Tone + Height * 12 + UpDown) / 12.0) * C3 + 0.5); //这里加0.5实现四舍五入
}

Buzzer::Buzzer(uint8_t pin)
{
    buzzerPin = pin;
    pinMode(pin, OUTPUT);
    tone(pin, 440);
    delay(50);
    noTone(pin);
}