#ifndef keyboard_H
#define keyboard_H
#include <arduino.h>

class keyboard44
{
private:
const char KBrow = 4;
const char KBcol = 4;
char KBkey[4][4]= {
    {11, 12, 13, 14},
    {21, 22, 23, 24},
    {31, 32, 33, 34},
    {41, 42, 43, 44}};
int KBdebounce = 20;
int KBrowPins[4] = {8, 9, 10, 11};
int KBcolPins[4] = {4, 5, 6, 7};
public:
keyboard44();
char getKey();
};

#endif