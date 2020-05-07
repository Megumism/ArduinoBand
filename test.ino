//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Music.h"
#include "Score.h"

enum TONE
{
    C,
    UC,
    D,
    UD,
    E,
    F,
    UF,
    G,
    UG,
    A,
    UA,
    B
};

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);
char key; //keyboard input

// LCD pin
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

int buzzer = 2;

//get information
Music music;

Score score;

void setup()
{
    //welcome
    Serial.begin(9600);
    pinMode(buzzer,OUTPUT);
}

//交互实现
void loop()
{
    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    lcd.begin(16, 2);
    score.writeNote(lcd, keyboard, 0);
    // for (char i = 0; i < 50; i++)
    // {
    //     char temp;
    //     temp = (score.writeNote(lcd, keyboard, i));
    //     if(temp = '-') i--;
    // }
}

int ToneX(enum TONE main, int SoundIN, bool up) //主调映射函数
{
    int Sound2Tone;
    int Sound2Height;
    int SoundOUT;
    if (SoundIN >= 0)
    {
        Sound2Tone = SoundIN % 10;
        Sound2Height = SoundIN / 10;
    }
    else
    {
        Sound2Tone = (-SoundIN) % 10;
        Sound2Height = -(((-SoundIN) / 10) + 1);
        // Serial.println(Sound2Tone);
        // Serial.println(Sound2Height);
    }
    if (Sound2Tone == 1)
        Sound2Tone = 0;
    else if (Sound2Tone == 2)
        Sound2Tone = 2;
    else if (Sound2Tone == 3)
        Sound2Tone = 4;
    else if (Sound2Tone == 4)
        Sound2Tone = 5;
    else if (Sound2Tone == 5)
        Sound2Tone = 7;
    else if (Sound2Tone == 6)
        Sound2Tone = 9;
    else if (Sound2Tone == 7)
        Sound2Tone = 11;
    SoundOUT = main - A + up + Sound2Tone + Sound2Height * 12;
    // Serial.println(SoundOUT);
    return int(pow(2, SoundOUT / 12.0) * 440.0 + 0.5); //这里加0.5实现四舍五入
}

void Sing(enum TONE Main, float Song[], int length, int beat)
{
    int sing;
    bool up;
    for (int i = 0; i < length; i++)
    {
        if (Song[i] != 0)
        {
            if (int(Song[i] * 2) % 2)
                up = true;
            else
                up = false;
            sing = Song[i];
            tone(buzzer, ToneX(Main, sing, up));
        }
        else
            noTone(buzzer);
        delay(beat);
    }
}
