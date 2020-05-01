#ifndef keyboard_H
#define keyboard_H
#include <arduino.h>

class keyboard44
{
private:
    const char KBrow = 4;
    const char KBcol = 4;
    char KBkey[4][4] = {
        {11, 12, 13, 14},
        {21, 22, 23, 24},
        {31, 32, 33, 34},
        {41, 42, 43, 44}};
    int KBdebounce = 20;
    int KBcolPins[4];
    int KBrowPins[4];

public:
    keyboard44(int pin1, int pin2, int pin3, int pin4, int pin5, int pin6, int pin7, int pin8); //键盘正面看下去从左往右数
    void setKey(char key, char row, char col);
    char getKey();
};

#endif