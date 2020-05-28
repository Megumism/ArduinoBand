#ifndef MusicGame_H
#define MusicGame_H
#include <Arduino.h>
#include "keyboard44.h"
#include "LiquidCrystal.h"
#include "MyBuzzer.h"
#include "Score.h"

class MusicGame
{
public:
    const int defaultMain = 6; //#F
    const int defaultBPM = 210;
    int defaultScore[67] = {
        -1061, -1071, 1011, 1021, 2031, 1061, 1051,
        2031, -2061, 1031, 1021, 1011, -1071,
        -1061, -1071, 1011, 1021, 2023, 1021, 1011,
        -1071, -1061, -1071, 1011, -1071, -1061, -1052, -1071,

        -1061, -1071, 1011, 1021, 2031, 1061, 1051,
        2031, -2061, 1031, 1021, 1011, -1071,
        -1061, -1071, 1011, 1021, 2023, 1021, 1011,
        -2071, 2011, 2021, 2031,

        1051, 1061, 1031, 1021, 2031, 1021, 1023,
        1051, 1061, 1031, 1021, 2031, 1021, 2023, 11111
        //1021,1011,-1071,-1051
    };

    void play(LiquidCrystal lcd, keyboard44 keyboard, Buzzer buzzer, int Note[], int main = 6, int BPM = 200);
};

#endif