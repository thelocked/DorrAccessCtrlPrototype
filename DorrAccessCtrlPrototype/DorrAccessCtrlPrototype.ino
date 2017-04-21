/*
 Name:		DorrAccessCtrlPrototype.ino

 Beskrivning:
	Applikationen ska se till att en dörr endast kan öppnas med hjälp av en kod.
	Dörren manuvres med hjälp av ett elektriskt elsutbläck som i strömlöst tillstånd
	blockerar möjligheten att öpnna dörren.
	Men om korrekt kod anges så matas låsfunktionen med spänning och slutar blockera öppning
	av dörren under en period

	Användaren har misst antal försök att mata in korrekt kod annars utlöses alarm trigger,
	som återställs efter en viss tid.

	En påbörjad inmatning nollställs efter en period.

Hur systemet används:
	Användaren matar in en siffer kombination via manöverpanelen, en kort perid grön indikering
	bekräftarknapptrykningen läst in och bekräftar med "#". Om användaren vill ångra påbörjad
	inmating så återställs den med "*".
	
	Om korrekt kod matats in så sluta dörren att blockeras så anvöndaren kan öppna
	Grönt fast sken indikerar att dörran kan öppnas.
	
	Om en felaktig kod matats in och inte överkrider andtal tillåtna felaktiga inmatningar,
	så meddelas dett med röd indikering och användare får nytt försök.
	Men skulle antalet felaktiga försök iföjld överskrida det tillåtna antalet,
	så aktiveras alarm under in viss tid.

	Skulle en användare mälja att mata in men inte bekräfta en kod eller
	av sluta efter ett eller flera felaktiga inmatningar, denna inmatings session
	att återställas efter en viss tid. Detta för att förhindra att en annan avändare inte
	ska kunna aktivera alarmet pga. tidigare inmatningar. Detta gör dock att en användare inte 
	har hur lång tid på sig som helst att mata in koden.





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