#pragma once
/*

            // <-- Knob (up)
           //
    B Gnd A 
	/  /  /

	 /  /
     C Gnd <-- Interchangeable
*/

class RotaryEncoder
{
private:
	int pin_A, pin_B, pin_C;

public:
	void setup(int pinA, int pinB);
	void setup(int pinA, int pinB, int pinC);

	void prepare();

	char getInput(int maxWait);
	char getInput();
};
