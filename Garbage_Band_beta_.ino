//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Music.h"
#include "string.h"
#define C3 261.63

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);
char key; //keyboard input

//pin of buzzer
int Buzzer = 2;

// LCD pin
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

//get information
Music music;

void setup()
{
    //welcome
    lcd.begin(16, 2); //设置列行值
    lcd.print("   Welcome to");
    lcd.setCursor(0, 1); //光标跳转到下一行

    lcd.print(" ");
    lcd.write(B10100010);
    lcd.print("Garbage Band");
    lcd.write(B10100011);

    delay(2000);

    pinMode(Buzzer, OUTPUT); //buzzer OUTPUT
    Serial.begin(9600);
}

//交互实现
void loop()
{
    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    lcd.begin(16, 2);
    if (music.songExisitence)
    {
        lcd.print("*:Song  D:Replay");
    }
    else
    {
        lcd.print("     *:Song     ");
    }
    lcd.setCursor(0, 1); //设置光标到第二行第一列
    lcd.print("     #:Game");

    key = 0;
    while (key == 0)
    {
        key = keyboard.getKey();
    } //防止key=0时不执行任何if语句而不停刷新

    //*.song
    if (key == '*')
    {
        music.Initialize();            //everything initialized
        music.getTone(lcd, keyboard);  //sequence: ABCDEFG
        music.getPace(lcd, keyboard);  //get the pace
        music.getMetre(lcd, keyboard);  //get the metre
        music.getMusic(lcd, keyboard); //get the music

        //show recording for a while
        lcd.begin(16, 2);
        lcd.print("  Recording...");
        delay(1500);

        sing();     //play the music
        delay(500); //stop for a while
        score();     //review the score

        //complimentary: Amazing!|Back to menu..
        lcd.begin(16, 2);
        lcd.print("    Amazing!");
        lcd.setCursor(0, 1);
        lcd.print(" Back to menu..");
        delay(1500);
    }

    //#.game
    else if (key == '#')
    {
    }

    //D.Replay
    else if (key == 'D')
    {
        sing();     //play the music
        delay(500); //stop for a while
                
        //complimentary: Amazing!|Back to menu..
        lcd.begin(16, 2);
        lcd.print("    Amazing!");
        lcd.setCursor(0, 1);
        lcd.print(" Back to menu..");
        delay(1000);
    }
}

void sing()
{
    float Frequency, Duration;
    int sum = 0;

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);

    for (int i = 0; i < music.num; i++)
    {
        if (music.UpDown[i] == 1)
            lcd.print('#');
        if (music.UpDown[i] == -1)
            lcd.print('b');
        lcd.print(music.RealNote[i]);

        sum += music.Dura[i];
        Duration = float(music.Dura[i]) / music.Rhythm * 60 * 1000;
        Frequency = C3 * pow(1.059463, music.Note[i]);
        tone(Buzzer, Frequency, Duration);
        delay(Duration / float(music.Dura[i]));

        for (int j = 0; j <= music.Dura[i] - 2; j++)
        {
            lcd.print('-');
            delay(Duration / float(music.Dura[i]));
        }
        lcd.print(" ");

        if (sum % music.metre == 0) //一个小节的末尾
        {
            music.pinX++;                     //小节数++
            music.pin[music.pinX] = i + 1; //记录每一个小节开头音符对应的序号
            if (sum / music.metre == 1)       //第一个小节末尾，直接输出光标下移
            {
                lcd.print('|');
                lcd.setCursor(0, 1);
            }
            else //其余小节末尾，作翻页操作
            {
                lcd.clear();
                lcd.begin(16, 2);
                for (int j = music.pin[music.pinX - 1]; j <= i; j++)
                {
                    lcd.print(music.RealNote[j]);
                    for (int k = 0; k <= music.Dura[j] - 2; k++)
                        lcd.print('-');
                    lcd.print(" ");
                }
                lcd.print('|');
                lcd.setCursor(0, 1);
            }
        }
    }
    music.pin[music.num + 1] = music.num;
}

void score()
{
    int head = 0;
    lcd.begin(16, 2);
    key = 0;

    for (int i = 0; i < music.pin[1]; i++)
    {
        lcd.print(music.RealNote[i]);
        for (int j = 0; j <= music.Dura[i] - 2; j++)
            lcd.print('-');
        lcd.print(' ');
    }
    lcd.print('|');
    lcd.setCursor(0, 1);
    for (int i = music.pin[1]; i < music.pin[2]; i++)
    {
        lcd.print(music.RealNote[i]);
        for (int j = 0; j <= music.Dura[i] - 2; j++)
            lcd.print('-');
        lcd.print(' ');
    }
    lcd.print('|');

    while (key != 'D')
    {
        key = keyboard.getKey();
        if (key == 'B')
            head--;
        if (key == 'C')
            head++;
        if (key != 0) //prevent non-stop refresh
        {
            lcd.clear();
            lcd.setCursor(0, 0);
            for (int i = music.pin[head]; i < music.pin[head + 1]; i++)
            {
                lcd.print(music.RealNote[i]);
                for (int j = 0; j <= music.Dura[i] - 2; j++)
                    lcd.print('-');
                lcd.print(' ');
            }
            lcd.print('|');
            lcd.setCursor(0, 1);
            for (int i = music.pin[head + 1]; i < music.pin[head + 2]; i++)
            {
                lcd.print(music.RealNote[i]);
                for (int j = 0; j <= music.Dura[i] - 2; j++)
                    lcd.print('-');
                lcd.print(' ');
            }
            lcd.print('|');
        }
    }
}
