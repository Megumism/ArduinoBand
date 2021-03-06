//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Score.h"
#include "MyBuzzer.h"
#include "MusicGame.h"

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);
Buzzer buzzer(2);
Score score;
MusicGame musicGame;

void setup()
{
    buzzer.test();
    //welcome
    lcd.begin(16, 2); //设置列行值
    lcd.print("   Welcome to");
    lcd.setCursor(0, 1); //光标跳转到下一行
    lcd.print(" ");
    lcd.write(B10100010);
    lcd.print("Garbage Band");
    lcd.write(B10100011);

    delay(2000);

    Serial.begin(9600);
}

//交互实现
void loop()
{
    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    lcd.begin(16, 2);
    if (score.length)
    {
        lcd.print("    #:Play     ");
        lcd.setCursor(0, 1); //设置光标到第二行第一列
        lcd.print("   *:Remake    ");
    }
    else
    {
        lcd.print("     #:Play    ");
        lcd.setCursor(0, 1); //设置光标到第二行第一列
        lcd.print("  *:Make Song  ");
    }

    int key = 0;
    while (key == 0)
    {
        key = keyboard.getKey();
    } //防止key=0时不执行任何if语句而不停刷新

    //*.song
    if (key == '*')
    {
        score.Initialize();           //everything initialized
        score.getTone(lcd, keyboard); //sequence: ABCDEFG
        while(!score.getBPM(lcd, keyboard));  //get the pace
        // score.getMetre(lcd, keyboard); //get the metre

        for (int i = 0; i < 50; i++)
        {
            char temp;
            temp = score.writeNote(lcd, keyboard, i);
            if (temp == '-')
                i--;
            if (temp == 'D'){
                score.note[i]=11111;
                break;
            }
            if (temp == '0')
                continue;
            buzzer.Sing(score.Tone, score.note[i]);
        }

        lcd.begin(16, 2);
        lcd.print("  Playing...");
        delay(300);
        buzzer.Sing(score);

        //complimentary: Amazing!|Back to menu..
        lcd.begin(16, 2);
        lcd.print("    Amazing!");
        lcd.setCursor(0, 1);
        lcd.print(" Back to menu..");
        delay(1500);
    }

    //#.Default
    else if (key == '#' && !score.length)
    {
        musicGame.play(lcd,keyboard,buzzer,musicGame.defaultScore);
    }

    //#.Guess
    else if (key == '#' && score.length)
    {
        lcd.begin(16, 2);
        lcd.print("  Replaying...");
        // buzzer.Sing(score); //play the music
        // delay(500);         //stop for a while
        musicGame.play(lcd,keyboard,buzzer,score.note,score.length,score.Tone,score.BPM);
        delay(500);
        //complimentary: Amazing!|Back to menu..
        lcd.begin(16, 2);
        lcd.print("    Amazing!");
        lcd.setCursor(0, 1);
        lcd.print(" Back to menu..");
        delay(500);
    }
}
