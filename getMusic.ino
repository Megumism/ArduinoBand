#include "getThing.h"
void getThing::getMusic()
{
    //输入乐谱，乐谱输入格式：升降+音符名+0+拍数，例如b1203，表示降D4(re)持续3拍；每输入一个音符按A回车，全部输入按D结束录入；B表示负号，-702，B3(si)持续两拍
    lcd.begin(16, 2);
    lcd.print("Your song:");
    lcd.setCursor(0, 1);
    lcd.blink();
    key = 0;
    num = 0;
    note = 0;
    Zflag = 0;
    Bflag = 0; //num为当前输入的音符数，读取时从0开始；note将输入的字符转换为数字并且暂存，比如负数的转换；Zflag标志有无输入音符节拍分隔符0；Bflag标志有无输入负号;

    //保持记录直到输入全曲终止符D
    while (key != 'D')
    {
        key = 0;
        key = keyboard.getKey();

        //检测到音符输入且不为A,D
        if ((key != 0) && (key != 'A') && (key != 'D'))
        {

            //修正B，7，8，9的输入
            if (key == 'B')
            {
                lcd.print('-');
                Bflag++;
            }
            else if ((key >= 'E') && (key <= 'G'))
            {
                lcd.print(key - '>');
            } //E，F，G恢复为7，8，9
            else
            {
                lcd.print(key);
            }
            delay(200);

            //对getKey的处理

            if (key == 'b')
                UpDown[num] = -1; //降号
            if (key == '#')
                UpDown[num] = 1; //升号

            //对1-6判断输入的是音符还是拍数
            if ((key >= '1') && (key <= '6'))
            {
                if (Zflag != 0)
                    Dura[num] = 10 * Dura[num] + (key - '0');
                else
                    note = 10 * note + (key - '0');
            }

            //对7-9判断输入的是音符还是拍数
            if ((key >= 'E') && (key <= 'G'))
            {
                if (Zflag)
                    Dura[num] = 10 * Dura[num] + (key - '>'); //查ASCII Table
                else
                    note = 10 * note + (key - '>');
            }

            //检测分隔符0
            if (key == '0')
            {
                Zflag++;
            }

            //检测负号B
            if (key == 'B')
            {
                Bflag++;
            }
        }

        //检测到当前音符输入完毕
        if (key == 'A')
        {

            //对当前音符信息的整合

            //对负号的分析
            if (!Bflag)
            {
                Note[num] = 12 * (note / 10) + TONE[(note % 10) - 1] + UpDown[num] + Tone; //与中央C的距离，比如对于#4，Note记录的值为6
            }
            else
            {
                Note[num] = TONE[(note % 10) - 1] + UpDown[num] + Tone - 12 * (note / 10 + 1); //与中央C的距离，比如对于b-7，Note记录的值为-2
            }

            RealNote[num] = note % 10;
            num++; //音符数+1
            Bflag = 0;
            Zflag = 0;
            note = 0; //Bflag，Zflag，note初始化

            //清空显示屏并显示“Your song:”，继续记录
            lcd.begin(16, 2);
            lcd.print("Your song:");
            lcd.setCursor(0, 1);
            lcd.blink();
        }
    }
}