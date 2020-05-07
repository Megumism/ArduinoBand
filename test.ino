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
void Sing(enum TONE Main, int Song[], char beat[], int length, int buzzer);

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
    tone(buzzer, 440);
    delay(50);
    noTone(buzzer);
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
        Serial.print("score.note[");
        Serial.print(i);
        Serial.print("]=");
        Serial.println(score.note[i]);
        tone(buzzer, ToneX(C, score.note[i]));
        delay(500);
        noTone(buzzer);
    }
    Sing(C, score.note, score.pace, i, buzzer);
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

void Sing(enum TONE Main, int Song[], char beat[], int length, int buzzer)
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
            tone(buzzer, ToneX(Main, Song[i]));
        }
        else
            noTone(buzzer);
        delay(int(beat[i]) * 500); //500要改掉的
    }
    noTone(buzzer);
}
