#ifndef MyBuzzer_H
#define MyBuzzer_H
#include <Arduino.h>

#ifndef C3
#define C3 261.63
#endif

#ifndef TONES
#define C 0
#define UC 1
#define D 2
#define UD 3
#define E 4
#define F 5
#define UF 6
#define G 7
#define UG 8
#define A 9
#define UA 10
#define B 11
#endif

class Buzzer
{
private:
    uint8_t buzzerPin;

public:
    int ToneX(int main, int SoundIN); //主调映射函数
    void Sing(int Main, int Song[], char beat[], int length);//唱一段
    void Sing(int Main, int Note, char beat);//唱一个
    Buzzer(uint8_t pin);//Beeee~
};

#endif