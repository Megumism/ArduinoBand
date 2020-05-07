#ifndef Score_H
#define Score_H
#include <Arduino.h>
#include "keyboard44.h"
#include "LiquidCrystal.h"

class Score
{
private:
    char cursorX = 0, cursorY = 0;  //记录光标位置
    bool cursorAvailable[16] = {0}; //防止光标越界

public:
    int note[50]={0};//例：-171
    char pace[50]={0};
    char writeNote(LiquidCrystal lcd, keyboard44 keyboard, int num);//返回0表示休止，返回-表示延音，返回1表示正常音符
};

#endif