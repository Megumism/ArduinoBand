#ifndef GetThing_H
#define GetThing_H
#include <arduino.h>
#include "LiquidCrystal.h"
#include "keyboard44.h"

class GetThing
{
private:
	const int TONE[7] = {0, 2, 4, 5, 7, 9, 11};	 //tone sequence: CDEFGAB
	const int TONE2[7] = {9, 11, 0, 2, 4, 5, 7}; //a new TONE for ABCDEFG

public:
	//data of music
	int UpDown[100] = {0};	 // b or #
	int Note[100] = {0};	 // record the number of note: 1, 7, 13
	int Dura[100] = {0};	 // duration
	int RealNote[100] = {0}; // record the note from 1 to 7
	int pin[100] = {0};
	//Tone:distance from C3( E is +4 ); Rhythm:BPM; metre:小节拍数; num:the total number of notes; pinX:小节数
	int Tone = 0, Rhythm = 0, metre = 0, num = 0, pinX = 0;
	bool songExisitence = false;//是否有歌

	void getTone(LiquidCrystal lcd, keyboard44 keyboard);
	void getPace(LiquidCrystal lcd, keyboard44 keyboard);
	void getMetre(LiquidCrystal lcd, keyboard44 keyboard);
	void getMusic(LiquidCrystal lcd, keyboard44 keyboard);
	void Initialize();
};

#endif
