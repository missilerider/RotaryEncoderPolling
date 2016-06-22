#include "RotaryEncoderPolling.h"

const int pin_A = 2; // Encoder input pins (rotary A)
const int pin_B = 4; // Rotary B
const int pin_C = 6; // Push button

RotaryEncoder enc;

void setup()
{
	Serial.begin(9600);
	enc.setup(pin_A, pin_B, pin_C);
	enc.prepare();
}

void loop()
{
	char d = enc.getInput(3);
	switch (d)
	{
	case 1: Serial.print("L"); break;
	case 2: Serial.print("R"); break;
	case 3: Serial.print("B"); break;
	case -1: Serial.print("T"); break;
	}
}
