#ifndef Score_H
#define Score_H
#include <Arduino.h>
#include "keyboard44.h"
#include "LiquidCrystal.h"

class Score
{
private:
    char cursorX = 0, cursorY = 0; //记录光标位置

public:
    int BPM = 0;
    int note[50] = {0}; //例：-1171 节拍-音-升降 1拍降2八度7无升降
    char length = 0;
    int Tone = 0;
    //返回0表示休止，返回-表示延音，返回1表示正常音符
    char writeNote(LiquidCrystal lcd, keyboard44 keyboard, int num);
    void getTone(LiquidCrystal lcd, keyboard44 keyboard);
    bool getBPM(LiquidCrystal lcd, keyboard44 keyboard);
    void getMetre(LiquidCrystal lcd, keyboard44 keyboard);
    void Initialize();
};

#endif