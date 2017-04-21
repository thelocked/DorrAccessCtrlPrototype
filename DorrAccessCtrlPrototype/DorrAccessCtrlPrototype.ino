/*
 Name:		DorrAccessCtrlPrototype.ino

 Beskrivning:
	Applikationen ska se till att en d�rr endast kan �ppnas med hj�lp av en kod.
	D�rren manuvres med hj�lp av ett elektriskt elsutbl�ck som i str�ml�st tillst�nd
	blockerar m�jligheten att �pnna d�rren.
	Men om korrekt kod anges s� matas l�sfunktionen med sp�nning och slutar blockera �ppning
	av d�rren under en period

	Anv�ndaren har misst antal f�rs�k att mata in korrekt kod annars utl�ses alarm trigger,
	som �terst�lls efter en viss tid.

	En p�b�rjad inmatning nollst�lls efter en period.

Hur systemet anv�nds:
	Anv�ndaren matar in en siffer kombination via man�verpanelen, en kort perid gr�n indikering
	bekr�ftarknapptrykningen l�st in och bekr�ftar med "#". Om anv�ndaren vill �ngra p�b�rjad
	inmating s� �terst�lls den med "*".
	
	Om korrekt kod matats in s� sluta d�rren att blockeras s� anv�ndaren kan �ppna
	Gr�nt fast sken indikerar att d�rran kan �ppnas.
	
	Om en felaktig kod matats in och inte �verkrider andtal till�tna felaktiga inmatningar,
	s� meddelas dett med r�d indikering och anv�ndare f�r nytt f�rs�k.
	Men skulle antalet felaktiga f�rs�k if�jld �verskrida det till�tna antalet,
	s� aktiveras alarm under in viss tid.

	Skulle en anv�ndare m�lja att mata in men inte bekr�fta en kod eller
	av sluta efter ett eller flera felaktiga inmatningar, denna inmatings session
	att �terst�llas efter en viss tid. Detta f�r att f�rhindra att en annan av�ndare inte
	ska kunna aktivera alarmet pga. tidigare inmatningar. Detta g�r dock att en anv�ndare inte 
	har hur l�ng tid p� sig som helst att mata in koden.





*/

#include "PinCode.h"
#include <OnewireKeypad.h> //For info: http://playground.arduino.cc/Code/OneWireKeyPad

//***Global Const and properties

PinCode doorPinCode = PinCode("1234"); //Provide pincode for door access

#define userInputRetriesAllowed = 3 //How many times the user may enter wrong pin bef alarmt trigger.

#define userInputResetDelay = 30000 //How long any input session from keypad will stored in millis
#define doorAccessEnabledPeriod = 15000//How long the user is abled to open door millis.

#define alarmTriggeredPeriod = 60000//How long will the alarm output stay triggered millis.


//**Pin configuration on the arduino

#define KEYPAD_PIN A0 //Pin input used for reading input from the keyboard hardware.
#define LED_OK_PIN 5 //Pin output used for display feedback to user. For door accsess granted and i key is pressed.
#define LED_ERR_PIN 6 //Pin out put used to inform user of wrong pin entered, alarm is triggerd and input reseted.
#define DOOR_ACCESS_PIN 7 //Pin output used to enable the lock to stop blocking door access.
#define ALARM_PIN 8 //Pin output for triggering alarm.



//** Keypad hardware setup and layout Settings
#define keypadRows 4
#define keypadCols 3
#define keypadRow_Res 4700
#define keypadCol_Res 1000
#define Precision ExtremePrec 

char keyPadKEYS[] = {
	'1','2','3',
	'4','5','6',
	'7','8','9',
	'*','0','#'
};

//Object that gets input from keypadharware
OnewireKeypad <Print, 12> KeyPad(Serial, keyPadKEYS, keypadRows, keypadCols, KEYPAD_PIN, keypadRow_Res, keypadCol_Res, Precision);

long LastkeyPressedTime = 0; //last input from user if not reseted..
long doorLockOpenTime = 0; //is access or when was the lock opened.
long alarmTriggerTime = 0; //is or when was the alarm triggerd.

char KeyPressed;
char lastKeyPressed;
char lastPinInput;
String pincodeInput = ""; //Stores input from keyPad by user.




// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600); //For debbugging output.

	//Set the pin modes and start values
	pinMode(ALARM_PIN, OUTPUT);
	pinMode(LED_ERR_PIN, OUTPUT);
	pinMode(DOOR_ACCESS_PIN, OUTPUT);
	pinMode(LED_OK_PIN, OUTPUT);

	digitalWrite(ALARM_PIN, LOW); //No alarm triggers;
	digitalWrite(DOOR_ACCESS_PIN, LOW); //Doorlock is closed;
	digitalWrite(LED_OK_PIN, LOW); //Led inditation off.
	digitalWrite(LED_ERR_PIN, LOW); //Led off



	

	Serial.println("End of setup.");

}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//Check for input if a key is pressed on key pad
	byte KState = KeyPad.Key_State();

	if (KState == PRESSED)
	{
		if (KeyPressed = KeyPad.Getkey())
		{
			Serial << "Pressed: " << KeyPressed << "\n";
			switch (KeyPressed)
			{
			//case '*': checkPassword(); break;
			//case '#': password.reset(); break;
			//default: password.append(KeyPressed);
			}
		}
	}
	else if (KState == HELD)
	{
		//Serial << "Key:" << KP.Getkey() << " being held\n";
	}
}

//Used for resetting current user input session
void resetSession()
{
	LastkeyPressedTime = 0; //last input from user if not reseted..
	doorLockOpenTime = 0; //is access or when was the lock opened.
	alarmTriggerTime = 0; //is or when was the alarm triggerd.

	//Print instruktions to serial window
	Serial.println("Enable door access by enter correct pincode and confirm with <ENTER>");
}