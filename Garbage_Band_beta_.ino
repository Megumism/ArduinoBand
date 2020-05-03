//Garbage Band Structure

#include "LiquidCrystal.h"
#include "keyboard44.h"
#include "Display.h"
#include "getThing.h"

//define the 4*4 keyboard
keyboard44 keyboard(11, 10, 9, 8, 7, 6, 5, 4);

//LCD display
Display Display;

//get information
getThing getThing;

//pin of buzzer
int Buzzer = 2;

//tone sequence: C, D, E, F, G, A, B
int TONE[7] = {0, 2, 4, 5, 7, 9, 11};

//data of music
int UpDown[100] = {0};   // b or # 
int Note[100] = {0};     // record the number of note: 1, 7, 13
int Dura[100] = {0};     // duration
int RealNote[100] = {0}; // record the note from 1 to 7

char key; //keyboard input

int Tone, Rhythm, num, note, Bflag, Zflag;
float Frequency, Duration, xx, sum = 0;

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); // LCD pin

void setup()
{
    Display.welcome(); //welcome
    pinMode(Buzzer, OUTPUT); //buzzer OUTPUT
    Serial.begin(9600);
}

void loop()
{
  
    Display.menu(); //show the menu
    
    //*.song
    if (key == '*')
    {
        getThing.getTone(); //sequence:C D E F G A B!
        getThing.getPace(); //get the pace
        getThing.getMusic(); //get the music
        Display.recording(); //show recording for a while
        Display.music(); //play the music
        delay(1000); //stop for a while
        Display.Amazing(); //complimentary   
    }

    //#.game
    else if (key == '#')
    {
    }

    Initialize(); //everything initialized
}

void Initialize()
{
    for (int i = 0; i <= num; i++)
    {
        Note[i] = 0;
        UpDown[i] = 0;
        Dura[i] = 0;
        RealNote[i] = 0; //initialize and prepare for next song
    }
}
