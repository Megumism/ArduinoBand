const char row = 4;
const char col = 4;
const char key[row][col] = {
    {11, 12, 13, 14},
    {21, 22, 23, 24},
    {31, 32, 33, 34},
    {41, 42, 43, 44}};
const int debounce = 20;
const int rowPins[row] = {4, 5, 6, 7};
const int colPins[col] = {8, 9, 10, 11};

bool tested = false;

void setup()
{
    Serial.begin(9600);
    for (int i = 0; i < col; i++)//列设为输出高电平
    {
        pinMode(colPins[i], OUTPUT);
        digitalWrite(colPins[i], HIGH);
        Serial.print(colPins[i]);
        Serial.println(" Setup finished");
    }
    for (int i = 0; i < row; i++)//行设为读取，初始化为高
    {
        pinMode(rowPins[i], INPUT);
        digitalWrite(rowPins[i], HIGH);
        Serial.print(rowPins[i]);
        Serial.println(" Setup finished");
    }
}

void loop()
{
    int key = getKey();
    if (key)
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
            // if (!tested)
            // {
            //     Serial.print(digitalRead(rowPins[j]));
            //     Serial.print(i);
            //     Serial.println(j);
            // }
            if (digitalRead(rowPins[j]) == LOW)
            {
                delay(debounce);
                while (digitalRead(rowPins[j]) == LOW); //一个有风险的死循环
                input = key[i][j];
            }
        }
        digitalWrite(colPins[i], HIGH);
    }
    tested = true;
    return input;
}