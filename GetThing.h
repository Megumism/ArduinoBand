#ifndef GetThing_H
#define GetThing_H
#include<arduino.h>
#include "keyboard44.h"

class GetThing
{
public:
	void getTone(LiquidCrystal lcd,keyboard44 keyboard);
	void getPace(LiquidCrystal lcd,keyboard44 keyboard);
	void getMusic(LiquidCrystal lcd,keyboard44 keyboard);
};
#endif
