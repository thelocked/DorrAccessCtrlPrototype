// PinCode.h

#ifndef _PINCODE_h
#define _PINCODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class PinCode
{

 public:
	 PinCode(char* pincode);
	 void addInput(char addInput);
	 void reset();
	 bool checkPin();



	 
private:
	String userInput;
	String correctPin;
};


#endif

