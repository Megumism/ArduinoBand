#include "keyboard44.h"

//从左到右写针脚
keyboard44::keyboard44(const uint8_t pin1, const uint8_t pin2, const uint8_t pin3, const uint8_t pin4, const uint8_t pin5, const uint8_t pin6, const uint8_t pin7, const uint8_t pin8)
{
    KBcolPins[0] = pin1;
    KBcolPins[1] = pin2;
    KBcolPins[2] = pin3;
    KBcolPins[3] = pin4;
    KBrowPins[0] = pin5;
    KBrowPins[1] = pin6;
    KBrowPins[2] = pin7;
    KBrowPins[3] = pin8;

    for (int i = 0; i < KBcol; i++) //列设为输出高电平
    {
        pinMode(KBcolPins[i], OUTPUT);
        digitalWrite(KBcolPins[i], HIGH);
        Serial.print(KBcolPins[i]);
        Serial.println(" Setup finished"); //调试用语句
    }
    for (int i = 0; i < KBrow; i++) //行设为读取，开启上拉电阻（为了复位）
    {
        pinMode(KBrowPins[i], INPUT);
        digitalWrite(KBrowPins[i], HIGH);
        Serial.print(KBrowPins[i]);
        Serial.println(" Setup finished"); //调试用语句
    }
}

//从注意零开始算行列
void keyboard44::setKey(char key, char row, char col)
{
    KBkey[row][col] = key;
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