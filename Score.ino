#include "Score.h"

char Score::writeNote(LiquidCrystal lcd, keyboard44 keyboard, int num)
{
    char key = 0;
    char buffer[4] = {0};
    char charnum = 0;  //记录buffer中的有效字符数
    if (cursorX >= 15) //换行
    {
        cursorY = 1;
        cursorX = 0;
    }
    char cursorX0 = cursorX, cursorY0 = cursorY; //记录初始位置
    lcd.setCursor(cursorX, cursorY);
    lcd.blink();
    while (key != 'D' && key != 'C')
    {
        key = keyboard.getKey();
        if (key == '#') //升
        {
            if (!buffer[0])
            {
                charnum++;
                cursorX++;
            }
            buffer[0] = key;
        }
        if (key == '*') //降
        {
            if (!buffer[0])
            {
                charnum++;
                cursorX++;
            }
            buffer[0] = 'b';
        }
        if (key == '9') //低度
        {
            if (!buffer[1])
            {
                charnum++;
                cursorX++;
            }
            buffer[1] = '-';
        }
        if (key == 'A' && cursorX > cursorX0)
        {
            cursorX = cursorX0;
            charnum = 0;
            for (int i = 0; i < 4; i++)
            {
                buffer[i] = 0;
            }
        }
        if (cursorX >= cursorX0 + 2 - !buffer[0] - !buffer[1] && cursorX <= cursorX0 + 3 - !buffer[0] - !buffer[1]) //允许写入状态
        {
            if (key >= '1' && key <= '7') //输入数字
            {
                buffer[cursorX - cursorX0 + !buffer[0] + !buffer[1]] = key;
                cursorX++;
                charnum++;
            }
        }
        if (key == 'D' || key == 'C')
        {
            break;
        }
        if (key == '0' && buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0) //休止符
        {
            lcd.write('0');
            cursorX++;
            break;
        }
        if (key == '8' && buffer[0] == 0 && buffer[1] == 0 && buffer[2] == 0 && buffer[3] == 0 && num) //延音
        {
            lcd.write('-');
            cursorX++;
            break;
        }
        //开始写入
        if (key != 0)
        {
            lcd.setCursor(cursorX0, cursorY0);
            if (cursorX0 + charnum > 15) //换行
            {
                lcd.print("    ");
                cursorX -= cursorX0;
                cursorX0 = 0;
                cursorY = 1;
                cursorY0 = 1;
                lcd.setCursor(cursorX0, cursorY0);
            }
            if (key == 'A')
                lcd.print("    ");
            else
            {
                if (buffer[0])
                    lcd.write(buffer[0]);
                if (buffer[1])
                    lcd.write(buffer[1]);
                for (char i = 2; i < 4; i++)
                {
                    if (buffer[i])
                        lcd.write(buffer[i]);
                    else
                        lcd.write(" ");
                }
            }

            Serial.print("(");
            Serial.print(int(cursorX));
            Serial.print(",");
            Serial.print(int(cursorY));
            Serial.print(") ");
            Serial.print(int(buffer[0]));
            Serial.print(int(buffer[1]));
            Serial.print(int(buffer[2]));
            Serial.print(int(buffer[3]));
            Serial.print(" ");
            Serial.println(int(charnum));

            key = 0;
            lcd.setCursor(cursorX, cursorY);
        }
    }
    cursorX++;//空一格
    if (key == 'D' && !charnum)
    {
        Serial.println("exit");
        return 'D';
    }
    if (key == '8')
    {
        pace[num - 1]++;
        return '-';
    }
    if (key == '0')
    {
        note[num] = 0;
        pace[num] = 1;
        return '0';
    }
    if (buffer[3])
        note[num] += 100 * (buffer[2] - '0') + 10 * (buffer[3] - '0');
    else
        note[num] += 10 * (buffer[2] - '0');
    if (!buffer[0])
        note[num] += 1;
    else if (buffer[0] == '#')
        note[num] += 2;
    else if (buffer[0] == 'b')
        note[num] += 0;
    if (buffer[1] == '-')
        note[num] = 0 - note[num];
    pace[num] = 1;
    return '1';
}