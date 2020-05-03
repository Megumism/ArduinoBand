#ifndef keyboard_H
#define keyboard_H
#include <arduino.h>

class keyboard44
{
private:
    const char KBrow = 4;
    const char KBcol = 4;
    char KBkey[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};
    int KBdebounce = 20;
    uint8_t KBcolPins[4];
    uint8_t KBrowPins[4];

public:
    keyboard44(const uint8_t pin1 = 4, const uint8_t pin2 = 5, const uint8_t pin3 = 6, const uint8_t pin4 = 7, const uint8_t pin5 = 8, const uint8_t pin6 = 9, const uint8_t pin7 = 10, const uint8_t pin8 = 11);
    void setKey(char key, char row, char col);
    char getKey();
};

#endif
