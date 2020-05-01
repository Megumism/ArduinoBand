#include "keyboard44.h"

keyboard44::keyboard44(){
    for (int i = 0; i < KBcol; i++)//列设为输出高电平
    {
        pinMode(KBcolPins[i], OUTPUT);
        digitalWrite(KBcolPins[i], HIGH);
        Serial.print(KBcolPins[i]);
        Serial.println(" Setup finished");//调试用语句
    }
    for (int i = 0; i < KBrow; i++)//行设为读取，开启上拉电阻（为了复位）
    {
        pinMode(KBrowPins[i], INPUT);
        digitalWrite(KBrowPins[i], HIGH);
        Serial.print(KBrowPins[i]);
        Serial.println(" Setup finished");//调试用语句
    }
}

char keyboard44::getKey()
{
    char input = 0;
    for (int i = 0; i < KBcol; i++)
    {
        digitalWrite(KBcolPins[i], LOW);
        for (int j = 0; j < KBrow; j++)
        {
            if (digitalRead(KBrowPins[j]) == LOW)
            {
                delay(KBdebounce);
                while (digitalRead(KBrowPins[j]) == LOW)
                    ; //一个有风险的死循环
                input = KBkey[i][j];
            }
        }
        digitalWrite(KBcolPins[i], HIGH);
    }
    return input;
}