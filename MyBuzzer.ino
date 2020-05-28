#include "MyBuzzer.h"

void Buzzer::Sing(Score score)
{
    Serial.print("Buzzer Sing: ");
    Serial.print("length=");
    Serial.println(int(score.length));
    for (int i = 0; i < score.length; i++)
    {
        if (score.note[i] != 0)
        {
            tone(buzzerPin, ToneX(score.Tone, score.note[i]));
            //输出日志
            Serial.print("note[");
            Serial.print(i);
            Serial.print("]=");
            Serial.print(score.note[i]);
            Serial.print(",beat[");
            Serial.print(i);
            Serial.print("]=");
            Serial.println(int(score.note[i] / 1000));
        }
        delay(int(score.note[i]) * 60.0 / score.BPM);
    }
    noTone(buzzerPin);
    Serial.println("Buzzer Stop");
}

void Buzzer::Sing(int Main, int Note, char beat, int BPM)
{
    tone(buzzerPin, ToneX(0, Note));

    Serial.print("Buzzer Sing: ");
    Serial.print("note=");
    Serial.print(Note);
    Serial.print(",beat=");
    Serial.print(int(beat));

    delay(int(beat) * 60.0 / BPM * 1000);
    noTone(buzzerPin);

    Serial.println(" Buzzer Stop");
}

int Buzzer::ToneX(int main, int SoundIN)
{
    char Tone;
    char Height;
    char UpDown;
    int SoundOUT;
    SoundIN %= 1000;
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
}

void Buzzer::test()
{
    tone(buzzerPin, 440);
    delay(50);
    noTone(buzzerPin);
}