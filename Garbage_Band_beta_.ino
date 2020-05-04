//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Display.h"
#include "getThing.h"
#include "string.h"

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);

//LCD display
Display Display;

//get information
getThing getThing;

//pin of buzzer
int Buzzer = 2;

//data of music
int UpDown[100] = {0};   // b or #
int Note[100] = {0};     // record the number of note: 1, 7, 13
int Dura[100] = {0};     // duration
int RealNote[100] = {0}; // record the note from 1 to 7
int pin[100] = {0};

char key; //keyboard input

int Tone = 0, Rhythm = 0, metre = 0, num = 0, pinX = 0;
//Tone:distance from C3( E is +4 ); Rhythm:BPM; metre:小节拍数; num:the total number of notes; pinX:小节数

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); // LCD pin

void setup()
{
    Display.welcome();       //welcome
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

    //*.song
    if (key == '*')
    {
        getThing.getTone();  //sequence: ABCDEFG
        getThing.getPace();  //get the pace
        getThing.getMusic(); //get the music

        //show recording for a while
        lcd.begin(16, 2);
        lcd.print("  Recording...");
        delay(2000);

        Display.music();   //play the music
        delay(1000);       //stop for a while
        Display.score();   //review the score
        Display.Amazing(); //complimentary
    }

    //#.game
    else if (key == '#')
    {
    }

    Initialize(); //everything initialized
}

void Initialize()
{
    memset(UpDown, 0, sizeof(UpDown));
    memset(Note, 0, sizeof(Note));
    memset(Dura, 0, sizeof(Dura));
    memset(RealNote, 0, sizeof(RealNote));
    Tone = 0;
    Rhythm = 0;
    metre = 0;
    num = 0;
    pinX = 0;
}
