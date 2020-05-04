//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Display.h"
#include "getThing.h"
#include "string.h"

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);

//LCD display
Display Display;

//get information
getThing getThing;

//pin of buzzer
int Buzzer = 2;

//data of music
int UpDown[100] = {0};   // b or # 
int Note[100] = {0};     // record the number of note: 1, 7, 13
int Dura[100] = {0};     // duration
int RealNote[100] = {0}; // record the note from 1 to 7
int pin[100] = {0};

char key; //keyboard input

int Tone = 0, Rhythm = 0, metre = 0, num = 0, pinX = 0;
//Tone:distance from C3( E is +4 ); Rhythm:BPM; metre:小节拍数; num:the total number of notes; pinX:小节数

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); // LCD pin

void setup()
{
    Display.welcome(); //welcome
    pinMode(Buzzer, OUTPUT); //buzzer OUTPUT
    changeKey(); //change the key
    Serial.begin(9600);
}

void loop()
{
      
    Display.menu(); //show the menu
    
    //*.song
    if (key == '*')
    {
        getThing.getTone(); //sequence: ABCDEFG
        getThing.getPace(); //get the pace
        getThing.getMusic(); //get the music
        Display.recording(); //show recording for a while
        Display.music(); //play the music
        delay(1000); //stop for a while
        Display.score();  //review the score
        Display.Amazing(); //complimentary  
    }

    //#.game
    else if (key == '#')
    {
    }

    Initialize(); //everything initialized
}

void changeKey()
{
    //键值变更
    char KBkey[4][4] = {
        {'1', '2', '3', 'A'},
        {'4', '5', '6', 'B'},
        {'7', '8', '9', 'C'},
        {'*', '0', '#', 'D'}};
    for (char i = 0; i < 4; i++)
    {
        for (char j = 0; j < 4; j++)
        {
            keyboard.setKey(KBkey[i][j],i,j);
        }
    }
}

void Initialize()
{
    memset(UpDown, 0, sizeof(UpDown));
    memset(Note, 0, sizeof(Note));
    memset(Dura, 0, sizeof(Dura));
    memset(RealNote, 0, sizeof(RealNote));
    Tone = 0; Rhythm = 0; metre = 0; num = 0; pinX = 0;
}
