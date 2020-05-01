# include "keyboard44.h"
keyboard44 keyboard(A0);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    int key = keyboard.getKey();
    if (key)//调试键盘用语句
    {
        Serial.println(int(key));
    }
}