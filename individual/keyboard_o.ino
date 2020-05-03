/* const char row = 4;
const char col = 4;
const char key[row][col] = {
    {11, 12, 13, 14},
    {21, 22, 23, 24},
    {31, 32, 33, 34},
    {41, 42, 43, 44}};
const int debounce = 20;
const int rowPins[row] = {8, 9, 10, 11};
const int colPins[col] = {4, 5, 6, 7};

void setup()
{
    // Serial.begin(9600);
    for (int i = 0; i < col; i++)//列设为输出高电平
    {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);
        Serial.print(colPins[i]);
        Serial.println(" Setup finished");//调试用语句
    }
    for (int i = 0; i < row; i++)//行设为读取，开启上拉电阻（为了复位）
    {
        pinMode(rowPins[i], INPUT);
        digitalWrite(rowPins[i], HIGH);
        Serial.print(rowPins[i]);
        Serial.println(" Setup finished");//调试用语句
    }
}

void loop()
{
    int key = getKey();
    if (key)//调试用语句
    {
        Serial.println(int(key));
    }
}

char getKey()
{
    char input = 0;
    for (int i = 0; i < col; i++)
    {
        digitalWrite(colPins[i], LOW);
        for (int j = 0; j < row; j++)
        {
            if (digitalRead(rowPins[j]) == LOW)
            {
                delay(debounce);
                while (digitalRead(rowPins[j]) == LOW); //一个有风险的死循环
                input = key[i][j];
            }
        }
        digitalWrite(colPins[i], HIGH);
    }
    return input;
} */