#ifndef Display_H
#define Display_H
#include<arduino.h>

class Display
{
private:
    const float C3 = 261.63;
    
public:
    void welcome();
    void menu();
    void recording();
    void music();
    void Amazing();
    void score();
};

#endif
