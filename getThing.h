#ifndef getThing_H
#define getThing_H
#include<arduino.h>

class getThing
{
private:
    const int TONE[7] = {0, 2, 4, 5, 7, 9, 11}; //tone sequence: CDEFGAB
    const int TONE2[7] = {9, 11, 0, 2, 4, 5, 7}; //a new TONE for ABCDEFG
    
public:
	  void getTone();
	  void getPace();
	  void getMusic();
};

#endif
