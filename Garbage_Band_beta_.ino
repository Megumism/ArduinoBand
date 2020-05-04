//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "getThing.h"
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
GetThing getThing;

void setup()
{
    //welcome
    lcd.begin(16, 2); //设置列行值
    lcd.print("   Welcome to");
    lcd.setCursor(0, 1); //光标跳转到下一行
    lcd.print("  Garbage Band");
    delay(2000);

    pinMode(Buzzer, OUTPUT); //buzzer OUTPUT
    Serial.begin(9600);
}

bool songExisitence = false;

void loop()
{

    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    lcd.begin(16, 2); //设置列行值
    lcd.print("     *:Song");
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
        getThing.Initialize();            //everything initialized
        getThing.getTone(lcd, keyboard);  //sequence: ABCDEFG
        getThing.getPace(lcd, keyboard);  //get the pace
        getThing.getMusic(lcd, keyboard); //get the music

        //show recording for a while
        lcd.begin(16, 2);
        lcd.print("  Recording...");
        delay(2000);

        music();     //play the music
        delay(1000); //stop for a while
        score();     //review the score

        //complimentaryAmazing!|Back to menu..
        lcd.begin(16, 2);
        lcd.print("    Amazing!");
        lcd.setCursor(0, 1);
        lcd.print(" Back to menu..");
        delay(2000);
    }

    //#.game
    else if (key == '#')
    {
    }
}

void music()
{
    float Frequency, Duration;
    int sum = 0;

    lcd.begin(16, 2);
    lcd.setCursor(0, 0);

    for (int i = 0; i < getThing.num; i++)
    {
        if (getThing.UpDown[i] == 1)
            lcd.print('#');
        if (getThing.UpDown[i] == -1)
            lcd.print('b');
        lcd.print(getThing.RealNote[i]);

        sum += getThing.Dura[i];
        Duration = float(getThing.Dura[i]) / getThing.Rhythm * 60 * 1000;
        Frequency = C3 * pow(1.059463, getThing.Note[i]);
        tone(Buzzer, Frequency, Duration);
        delay(Duration / float(getThing.Dura[i]));

        for (int j = 0; j <= getThing.Dura[i] - 2; j++)
        {
            lcd.print('-');
            delay(Duration / float(getThing.Dura[i]));
        }
        lcd.print(" ");

        if (sum % getThing.metre == 0) //一个小节的末尾
        {
            getThing.pinX++;                     //小节数++
            getThing.pin[getThing.pinX] = i + 1; //记录每一个小节开头音符对应的序号
            if (sum / getThing.metre == 1)       //第一个小节末尾，直接输出光标下移
            {
                lcd.print('|');
                lcd.setCursor(0, 1);
            }
            else //其余小节末尾，作翻页操作
            {
                lcd.clear();
                lcd.begin(16, 2);
                for (int j = getThing.pin[getThing.pinX - 1]; j <= i; j++)
                {
                    lcd.print(getThing.RealNote[j]);
                    for (int k = 0; k <= getThing.Dura[j] - 2; k++)
                        lcd.print('-');
                    lcd.print(" ");
                }
                lcd.print('|');
                lcd.setCursor(0, 1);
            }
        }
    }
    getThing.pin[getThing.num + 1] = getThing.num;
}

void score()
{
    int head = 0;
    lcd.begin(16, 2);
    key = 0;

    for (int i = 0; i < getThing.pin[1]; i++)
    {
        lcd.print(getThing.RealNote[i]);
        for (int j = 0; j <= getThing.Dura[i] - 2; j++)
            lcd.print('-');
        lcd.print(' ');
    }
    lcd.print('|');
    lcd.setCursor(0, 1);
    for (int i = getThing.pin[1]; i < getThing.pin[2]; i++)
    {
        lcd.print(getThing.RealNote[i]);
        for (int j = 0; j <= getThing.Dura[i] - 2; j++)
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
            for (int i = getThing.pin[head]; i < getThing.pin[head + 1]; i++)
            {
                lcd.print(getThing.RealNote[i]);
                for (int j = 0; j <= getThing.Dura[i] - 2; j++)
                    lcd.print('-');
                lcd.print(' ');
            }
            lcd.print('|');
            lcd.setCursor(0, 1);
            for (int i = getThing.pin[head + 1]; i < getThing.pin[head + 2]; i++)
            {
                lcd.print(getThing.RealNote[i]);
                for (int j = 0; j <= getThing.Dura[i] - 2; j++)
                    lcd.print('-');
                lcd.print(' ');
            }
            lcd.print('|');
        }
    }
}
