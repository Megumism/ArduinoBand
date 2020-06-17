#include "MyBuzzer.h"

void Buzzer::Sing(Score score)
{
    Serial.print("Buzzer Sing: ");
    Serial.print("length=");
    Serial.println(int(score.length));
    for (int i = 0; i < score.length; i++)
    {
        //输出日志
        Serial.print("note[");
        Serial.print(i);
        Serial.print("]=");
        Serial.print(score.note[i]);
        Serial.print(",beat[");
        Serial.print(i);
        Serial.print("]=");
        Serial.println(int(score.note[i] / 1000));
        if (score.note[i] % 1000 != 0)
        {
            tone(buzzerPin, ToneX(score.Tone, score.note[i]));
        }
        else{
            noTone(buzzerPin);
        }
        delay(int(abs(score.note[i]) / 1000) * 60.0 / score.BPM * 1000);
    }
    noTone(buzzerPin);
    Serial.println("Buzzer Stop");
}

void Buzzer::Sing(int main, int Note, int BPM)
{
    tone(buzzerPin, ToneX(main, Note)); //要改

    Serial.print("Buzzer Sing: ");
    Serial.print("note=");
    Serial.print(Note);
    Serial.print(",beat=");
    Serial.print(int(abs(Note) / 1000));

    delay(int(abs(Note) / 1000) * 60.0 / BPM * 1000);
    noTone(buzzerPin);

    Serial.println(" Buzzer Stop");
}

int Buzzer::ToneX(int main, int SoundIN)
{
    char Tone;
    char Height;
    char UpDown;
    int SoundOUT;
    if (SoundIN >= 0)
    {
        SoundIN %= 1000;
        Tone = SoundIN % 100 / 10;
        Height = SoundIN / 100;
        UpDown = SoundIN % 10 - 1;
    }
    else
    {
        SoundIN = -(abs(SoundIN) % 1000);
        Tone = (-SoundIN) % 100 / 10;
        Height = -(((-SoundIN) / 100) + 1);
        UpDown = (-SoundIN % 10) - 1;
    }
    // Serial.println(int(SoundIN));
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
    // Serial.println(pow(2, (main + Tone + Height * 12 + UpDown) / 12.0) * C3 + 0.5);
    return int(pow(2, (main + Tone + Height * 12 + UpDown) / 12.0) * C3 - 0.5); //这里加0.5实现四舍五入
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