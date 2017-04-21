/*
 Name:		DorrAccessCtrlPrototype.ino

*/

#include <OnewireKeypad.h> //For info: http://playground.arduino.cc/Code/OneWireKeyPad

//***Global Const and properties

const String doorPinCode = "1234"; //The key sequence to enable door access
const byte doorPinCodeLengt = 4; //How many digits in keycode
const byte userInputRetries = 3; //How many times the user may enter wrong pin bef alarmt trigger.

const long userInputResetDelay = 30000; //How long any input session from keypad will stored
const long doorAccessEnabledPeriod = 15000;//How long the user is abled to open door.

const long alarmTriggeredPeriod = 60000;//How long will the alarm output stay triggered.

//**
String pincodeEnterd; //Stores input from keyPad.


#define Rows 4
#define Cols 3
#define Pin A0
#define Row_Res 4700
#define Col_Res 1000
					  // ExtremePrec, HighPrec, MediumPrec, LowPrec
#define Precision ExtremePrec 

char KEYS[] = {
	'1','2','3',
	'4','5','6',
	'7','8','9',
	'*','0','#'
};

OnewireKeypad <Print, 12> KeyPad(Serial, KEYS, Rows, Cols, Pin, Row_Res, Col_Res, Precision);




long keypadInputTime = 0; //last input from user if not reseted..
long doorLockOpenTime = 0; //is access or when was the lock opened.
long alarmTriggerTime = 0; //is or when was the alarm triggerd.







// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
