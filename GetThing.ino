#include "GetThing.h"
void GetThing::getTone(LiquidCrystal lcd,keyboard44 keyboard)
{
    char UDflag = ' ', Toneflag = 'C';     //UDflag:whether use */# or not; Toneflag:A-G
    int letter = 0;                        //0 means C, 1 means D
    int TONE2[7] = {9, 11, 0, 2, 4, 5, 7}; //a new TONE for ABCDEFG

    lcd.begin(16, 2);
    lcd.print("Tone:");
    lcd.setCursor(0, 1);
    lcd.print(" C");
    key = 0;
    Tone = 0;

    while (key != 'D')
    {
        key = keyboard.getKey();

        if (key != 0)
        {
            if (key == '*') // b flat
            {
                UDflag = 'b';
                Tone--;
            }
            if (key == '#') // # sharp
            {
                UDflag = key;
                Tone++;
            }
            if (key == 'B') // Up
            {
                letter++;
                Toneflag++;
            }
            if (key == 'C') // Down
            {
                letter--;
                Toneflag--;
            }
            //Display
            lcd.begin(16, 2);
            lcd.print("Tone:");
            lcd.setCursor(0, 1);
            lcd.print(UDflag);
            lcd.print(Toneflag);
        }
    }
    Tone += TONE2[letter + 2];
    Serial.println(Tone);
}

void GetThing::getPace(LiquidCrystal lcd,keyboard44 keyboard)
{
    //������ģ����ĸ�ʽ��120#����#��β
    lcd.begin(16, 2);
    lcd.print("Rhythm:");
    lcd.setCursor(0, 1);
    lcd.blink();
    key = 0;
    Rhythm = 0;

    //һֱ��¼���ݣ�ֱ��������ֹ��#
    while (key != '#')
    {
        key = keyboard.getKey();

        //��⵽��������
        if ((key != 0) && (key != '#'))
        {
            //����7��8��9����
            if ((key >= 'E') && (key <= 'G'))
            {
                key = key - 14;
            }
            lcd.print(key);
            Rhythm = 10 * Rhythm + (key - '0');
        }
    }
}

void GetThing::getMusic(LiquidCrystal lcd,keyboard44 keyboard)
{
    //�������ף����������ʽ������+������+0+����������b1203����ʾ��D4(re)����3�ģ�ÿ����һ��������A�س���ȫ�����밴D����¼�룻B��ʾ���ţ�-702��B3(si)��������
    lcd.begin(16, 2);
    lcd.print("Your song:");
    lcd.setCursor(0, 1);
    lcd.blink();
    key = 0;
    num = 0;
    note = 0;
    Zflag = 0;
    Bflag = 0; //numΪ��ǰ���������������ȡʱ��0��ʼ��note��������ַ�ת��Ϊ���ֲ����ݴ棬���縺����ת����Zflag��־���������������ķָ���0��Bflag��־�������븺��;

    //���ּ�¼ֱ������ȫ����ֹ��D
    while (key != 'D')
    {
        key = 0;
        key = keyboard.getKey();

        //��⵽���������Ҳ�ΪA,D
        if ((key != 0) && (key != 'A') && (key != 'D'))
        {

            //����B��7��8��9������
            if (key == 'B')
            {
                lcd.print('-');
                Bflag++;
            }
            else if ((key >= 'E') && (key <= 'G'))
            {
                lcd.print(key - '>');
            } //E��F��G�ָ�Ϊ7��8��9
            else
            {
                lcd.print(key);
            }
            delay(200);

            //��getKey�Ĵ���

            if (key == 'b')
                UpDown[num] = -1; //����
            if (key == '#')
                UpDown[num] = 1; //����

            //��1-6�ж��������������������
            if ((key >= '1') && (key <= '6'))
            {
                if (Zflag != 0)
                    Dura[num] = 10 * Dura[num] + (key - '0');
                else
                    note = 10 * note + (key - '0');
            }

            //��7-9�ж��������������������
            if ((key >= 'E') && (key <= 'G'))
            {
                if (Zflag)
                    Dura[num] = 10 * Dura[num] + (key - '>'); //��ASCII Table
                else
                    note = 10 * note + (key - '>');
            }

            //���ָ���0
            if (key == '0')
            {
                Zflag++;
            }

            //��⸺��B
            if (key == 'B')
            {
                Bflag++;
            }
        }

        //��⵽��ǰ�����������
        if (key == 'A')
        {

            //�Ե�ǰ������Ϣ������

            //�Ը��ŵķ���
            if (!Bflag)
            {
                Note[num] = 12 * (note / 10) + TONE[(note % 10) - 1] + UpDown[num] + Tone; //������C�ľ��룬�������#4��Note��¼��ֵΪ6
            }
            else
            {
                Note[num] = TONE[(note % 10) - 1] + UpDown[num] + Tone - 12 * (note / 10 + 1); //������C�ľ��룬�������b-7��Note��¼��ֵΪ-2
            }

            RealNote[num] = note % 10;
            num++; //������+1
            Bflag = 0;
            Zflag = 0;
            note = 0; //Bflag��Zflag��note��ʼ��

            //�����ʾ������ʾ��Your song:����������¼
            lcd.begin(16, 2);
            lcd.print("Your song:");
            lcd.setCursor(0, 1);
            lcd.blink();
        }
    }
}