//Garbage Band整体框架

#include "LiquidCrystal.h"

//中央C
float C3 = 261.63;

//蜂鸣器引脚
int Buzzer = 2;

//音调的数值次序:C,D,E,F,G,A,B
int TONE[7] = {0,2,4,5,7,9,11}; 

//乐谱记录数据：音高，时长
int UpDown[100] = {0}; //音符升降
int Note[100] = {0}; //音高（同C3相比）
int Dura[100] = {0}; //拍数
int RealNote[100] = {0}; //简谱

//4*4矩阵键盘的定义
const char KBrow = 4; //定义4行
const char KBcol = 4; //定义4列
char KBkey[4][4] = { //键值
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'E', 'F', 'G', 'C'},
    {'b', '0', '#', 'D'}
};
const int KBrowPins[4] = {7,6,5,4}; //设置硬件对应的引脚
const int KBcolPins[4] = {11,10,9,8};
const int KBdebounce = 20; //去抖时间长度

//液晶显示屏初始化引脚
LiquidCrystal lcd(12,13,A0,A1,3,A2);




void setup() {
    
    //4*4矩阵键盘初始化功能
    Serial.begin(9600);
    for (int row = 0; row < KBrow; row++)
    {
        pinMode(KBrowPins[row],INPUT);
        digitalWrite(KBrowPins[row],HIGH);
    }
    for (int col = 0; col < KBcol; col++)
    {
        pinMode(KBcolPins[col],OUTPUT);
        digitalWrite(KBcolPins[col],HIGH);
    }
    
    //打印欢迎语句 
    lcd.begin(16,2); //设置列行值
    lcd.print("   Welcome to");
    lcd.setCursor(0,1); //设置光标到第二行第一列
    lcd.print("  Garbage Band");
    delay(2000);
    
    //蜂鸣器引脚设置为输出
    pinMode(Buzzer,OUTPUT);
    
}




void loop() {
  
int Tone, Rhythm, num, note, Bflag, Zflag;
float Frequency, Duration, xx, sum = 0;
char key;


    //显示开始界面，并且让使用者选择：1.制谱 2.游戏
    lcd.begin(16,2); //设置列行值
    lcd.print("     *:Song");
    lcd.setCursor(0,1); //设置光标到第二行第一列
    lcd.print("     #:Game");


    key = 0;
    while (key == 0) {  key = getKey(); } //防止key=0时不执行任何if语句而不停刷新


    //*.制谱
    if (key == 'b') 
    {
    
        //输入主调，主调格式：*A，#B，C；*代表降调，但输出的是b
        lcd.begin(16,2);
        lcd.print("Tone:");
        lcd.setCursor(0,1);
        lcd.blink();
        key = 0; Tone = 0;
        
        //一直记录数据，直到输入完毕
        while ((key < 'A') || (key > 'G')) 
        {
            key = getKey();
            
            //检测到按键输入
            if (key != 0) 
            {
                lcd.print(key);
                delay(500);
                if (key == 'b') --Tone; //降调
                if (key == '#') ++Tone; //升调
                if (key == 'A') Tone += 9;
                if (key == 'B') Tone -= 1;
                if ((key >='C') && (key <= 'G')) Tone += TONE[key - 'C'];
                //Tone记录该调首音与中央C的距离，比如bB为-2，#A为10
            }
        }

    
        //输入节拍，节拍格式：120#，以#结尾
        lcd.begin(16,2);
        lcd.print("Rhythm:");
        lcd.setCursor(0,1);
        lcd.blink();
        key = 0; Rhythm = 0;
        
        //一直记录数据，直到输入终止符#
        while (key != '#') 
        {
            key = getKey();
            
            //检测到按键输入
            if ((key != 0) && (key != '#')) 
            {
                //修正7，8，9输入
                if ((key >= 'E') && (key <= 'G')) { key = key - 14; }
                lcd.print(key);
                Rhythm = 10*Rhythm + (key - '0') ;
            }
        }


        //输入乐谱，乐谱输入格式：升降+音符名+0+拍数，例如b1203，表示降D4(re)持续3拍；每输入一个音符按A回车，全部输入按D结束录入；B表示负号，-702，B3(si)持续两拍
        lcd.begin(16,2);
        lcd.print("Your song:");
        lcd.setCursor(0,1);
        lcd.blink();
        key = 0; num = 0; note = 0; Zflag = 0; Bflag = 0; //num为当前输入的音符数，读取时从0开始；note将输入的字符转换为数字并且暂存，比如负数的转换；Zflag标志有无输入音符节拍分隔符0；Bflag标志有无输入负号;
        
        //保持记录直到输入全曲终止符D
        while (key != 'D') {
            key = 0;
            key = getKey();
            
            //检测到音符输入且不为A,D
            if ((key != 0) && (key != 'A') && (key != 'D')) 
            {
              
                //修正B，7，8，9的输入
                if (key == 'B') { lcd.print('-'); Bflag++; }
                else
                if ((key >= 'E') && (key <= 'G')) { lcd.print(key - '>'); } //E，F，G恢复为7，8，9
                else 
                {  lcd.print(key); }
                delay(200);
                
                //对getKey的处理
                
                if (key == 'b') UpDown[num] = -1; //降号
                if (key == '#') UpDown[num] = 1;  //升号
                
                //对1-6判断输入的是音符还是拍数
                if ((key >= '1') && (key <= '6')) {
                    if (Zflag != 0) Dura[num] = 10*Dura[num] + (key - '0');
                    else note = 10*note + (key - '0');
                } 
                
                //对7-9判断输入的是音符还是拍数
                if ((key >= 'E') && (key <= 'G')) {
                    if (Zflag) Dura[num] = 10*Dura[num] + (key - '>'); //查ASCII Table
                    else note = 10*note + (key - '>');
                } 
                
                //检测分隔符0
                if (key == '0') { Zflag++;  }
                
                //检测负号B
                if (key == 'B') { Bflag++;  }
                
            }
            
            //检测到当前音符输入完毕
            if (key == 'A') 
            {

                //对当前音符信息的整合

                //对负号的分析
                if (!Bflag) 
                { 
                    Note[num] = 12 * (note/10) + TONE[ (note%10) - 1] + UpDown[num] + Tone; //与中央C的距离，比如对于#4，Note记录的值为6
                }
                else 
                {
                    Note[num] =  TONE[ (note%10) - 1] + UpDown[num] + Tone - 12 * (note/10 + 1); //与中央C的距离，比如对于b-7，Note记录的值为-2
                }

                Serial.print("Dura["); Serial.print(num); Serial.print("]:"); Serial.println(Dura[num]);
                Serial.print("Zflag:"); Serial.println(Zflag);
                Serial.print("Bflag:"); Serial.println(Bflag);

                RealNote[num] = note%10;
                num++; //音符数+1
                Bflag = 0; Zflag = 0; note = 0; //Bflag，Zflag，note初始化
                
                //清空显示屏并显示“Your song:”，继续记录
                lcd.begin(16,2);
                lcd.print("Your song:");
                lcd.setCursor(0,1);
                lcd.blink();
            }
        }

        
        //显示屏短暂显示“Recording…”
        lcd.begin(16,2);
        lcd.print("  Recording...");
        delay(2000);

        
        /*放歌，格式为 
          b7--- 6- 2- 4---
          乐谱随音乐滚动
        */
        lcd.begin(16,2);
        lcd.print("Enjoy Your song!");
        lcd.setCursor(0,1);
        for (int i = 0; i<num; i++)
        {
            
            //输出升降号
            if (UpDown[i] == 1) { lcd.print('#'); }
            if (UpDown[i] == -1) { lcd.print('b'); }
            
            //蜂鸣器发声
            xx = Dura[i] ; //变量类型转换
            sum += Dura[i];
            Duration = xx / Rhythm * 60 * 1000;
            Frequency = C3 * pow(1.059463,Note[i]);
            tone(Buzzer,Frequency,Duration);
            
            //输出简谱1-7
            lcd.print(RealNote[i]);
            if (sum >= 4) {  lcd.scrollDisplayLeft(); } //向左滚一滚

            //输出拍子
            delay(Duration/xx);
            for (int j=0; j<=Dura[i]-2; j++) 
            {  
                lcd.print('-'); delay(Duration/xx); 
                if (sum >= 12) {  lcd.scrollDisplayLeft(); } //向左滚拍子
            }

            lcd.print(" "); //音符之间的分隔
    
        }
        
        //留白
        delay(1000); 

        //屏幕显示“Amazing!|Back to menu..”数秒后，回到开始界面
        lcd.begin(16,2);
        lcd.print("    Amazing!");
        lcd.setCursor(0,1);
        lcd.print(" Back to menu..");
        delay(2000);
         
    }
    
    //#.游戏
    else if (key == '#') 
    {
    }

    for (int i = 0; i <= num; i++) 
    {
        Note[i] = 0; UpDown[i] = 0; Dura[i] = 0; RealNote[i] = 0; //数组数据清零，准备下一次song
    }

}


//读取键值程序
char getKey()
{
    char key = 0;
    for (int col = 0; col < KBcol; col++)
    {
        digitalWrite(KBcolPins[col], LOW);
        for (int row = 0; row < KBrow; row++)
        {
            if (digitalRead(KBrowPins[row]) == LOW)
            {
                delay(KBdebounce);
                while (digitalRead(KBrowPins[row]) == LOW) //一个有风险的死循环 
                    ;
                key = KBkey[3-row][3-col];
            }
        }
        digitalWrite(KBcolPins[col], HIGH);
    }
    return key;
}
