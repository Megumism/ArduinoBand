#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "GetThing.h"
#define C3 261.63

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);

//pin of buzzer
int Buzzer = 2;

// LCD pin
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); 

//get information
GetThing getThing;

//tone sequence: C, D, E, F, G, A, B
int TONE[7] = {0, 2, 4, 5, 7, 9, 11};

//data of music
int UpDown[100] = {0};   // b or #
int Note[100] = {0};     // record the number of note: 1, 7, 13
int Dura[100] = {0};     // duration
int RealNote[100] = {0}; // record the note from 1 to 7

char key; //keyboard input

int Tone, Rhythm, num, note, Bflag, Zflag;
float Frequency, Duration, xx, sum = 0;


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

    Initialize(); //everything initialized
}

void Initialize()
{
    for (int i = 0; i <= num; i++)
    {
        Note[i] = 0;
        UpDown[i] = 0;
        Dura[i] = 0;
        RealNote[i] = 0; //initialize and prepare for next song
    }
}

void musicVisualize()
{
    for (int i = 0; i < num; i++)
    {
        //���������
        if (UpDown[i] == 1)
            lcd.print('#');
        if (UpDown[i] == -1)
            lcd.print('b');

        //����������
        xx = Dura[i]; //��������ת��
        sum += Dura[i];
        Duration = xx / Rhythm * 60 * 1000;
        Frequency = C3 * pow(1.059463, Note[i]);
        tone(Buzzer, Frequency, Duration);

        //�������1-7
        lcd.print(RealNote[i]);
        if (sum >= 4)
        {
            lcd.scrollDisplayLeft();
        } //�����һ��

        //�������
        delay(Duration / xx);
        for (int j = 0; j <= Dura[i] - 2; j++)
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