//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Music.h"
#include "Score.h"
#define C3 261.63

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

int ToneX(enum TONE main, int SoundIN);
void Sing(enum TONE Main, float Song[], int length, int beat);

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
    lcd.begin(16, 2);
    Serial.begin(9600);
    pinMode(buzzer, OUTPUT);
}

//交互实现
void loop()
{
    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    score.writeNote(lcd, keyboard, 0);
    // for (char i = 0; i < 50; i++)
    // {
    //     char temp;
    //     temp = (score.writeNote(lcd, keyboard, i));
    //     if(temp = '-') i--;
    // }
}

int ToneX(enum TONE main, int SoundIN) //主调映射函数
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
    Serial.println(int(Tone));
    Serial.println(int(Height));
    Serial.println(int(UpDown));
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
    SoundOUT = main + Tone + Height * 12 + UpDown;
    Serial.println(SoundOUT);
    return int(pow(2, SoundOUT / 12.0) * C3 + 0.5); //这里加0.5实现四舍五入
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
            tone(buzzer, ToneX(Main, sing));
        }
        else
            noTone(buzzer);
        delay(beat);
    }
}
