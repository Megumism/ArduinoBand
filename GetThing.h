#ifndef GetThing_H
#define GetThing_H
#include <arduino.h>
#include "keyboard44.h"
#include "LiquidCrystal.h"

class GetThing
{
public:
	//tone sequence: C, D, E, F, G, A, B
	int TONE[7] = {0, 2, 4, 5, 7, 9, 11};

	//data of music
	int UpDown[100] = {0};	 // b or #
	int Note[100] = {0};	 // record the number of note: 1, 7, 13
	int Dura[100] = {0};	 // duration
	int RealNote[100] = {0}; // record the note from 1 to 7

	int Tone, Rhythm, num, note, Bflag, Zflag;

	void getTone(LiquidCrystal lcd, keyboard44 keyboard);
	void getPace(LiquidCrystal lcd, keyboard44 keyboard);
	void getMusic(LiquidCrystal lcd, keyboard44 keyboard);
	void Initialize();
};
#endif
