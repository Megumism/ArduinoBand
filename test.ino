//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Music.h"
#include "Score.h"

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);
char key; //keyboard input

// LCD pin
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

//get information
Music music;

Score score;

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

    delay(500);
    Serial.begin(9600);
}

//交互实现
void loop()
{
    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    lcd.begin(16, 2);
    score.writeNote(lcd,keyboard,1);
}
