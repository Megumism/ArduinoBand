#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "GetThing.h"
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
    //welcome欢迎语句
    lcd.begin(16, 2); //设置列行值
    lcd.print("   Welcome to");
    lcd.setCursor(0, 1); //光标跳转到下一行
    lcd.print("  Garbage Band");
    delay(2000);

    pinMode(Buzzer, OUTPUT); //buzzer OUTPUT
    Serial.begin(9600);
}

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

    if (key == '*')
    {
        getThing.getTone(lcd,keyboard);  //sequence:C D E F G A B!
        getThing.getPace(lcd,keyboard);  //get the pace
        getThing.getMusic(lcd,keyboard); //get the music

        //show recording for a while
        lcd.begin(16, 2);
        lcd.print("  Recording...");
        delay(2000);

        //play the music
        lcd.begin(16, 2);
        lcd.print("Enjoy Your song!");
        lcd.setCursor(0, 1);
        musicVisualize();

        //stop for a while
        delay(1000);

        //complimentary：Amazing!|Back to menu..
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

    getThing.Initialize(); //nitialized
}

void musicVisualize()
{
	float Frequency, Duration, xx, sum = 0;
    for (int i = 0; i < getThing.num; i++)
    {
        //���������
        if (getThing.UpDown[i] == 1)
            lcd.print('#');
        if (getThing.UpDown[i] == -1)
            lcd.print('b');

        //����������
        xx = getThing.Dura[i]; //��������ת��
        sum += getThing.Dura[i];
        Duration = xx / getThing.Rhythm * 60 * 1000;
        Frequency = C3 * pow(1.059463, getThing.Note[i]);
        tone(Buzzer, Frequency, Duration);

        //�������1-7
        lcd.print(getThing.RealNote[i]);
        if (sum >= 4)
        {
            lcd.scrollDisplayLeft();
        } //�����һ��

        //�������
        delay(Duration / xx);
        for (int j = 0; j <= getThing.Dura[i] - 2; j++)
        {
            lcd.print('-');
            delay(Duration / xx);
            if (sum >= 12)
            {
                lcd.scrollDisplayLeft();
            } //���������
        }
    }
    lcd.print(" "); //����֮��ķָ�
}