#include <Arduino.h>
#include "RotaryEncoderPolling.h"

void RotaryEncoder::setup(int pinA, int pinB)
{
	pin_A = pinA;
	pin_B = pinB;
	pin_C = 0;
}

void RotaryEncoder::setup(int pinA, int pinB, int pinC)
{
	pin_A = pinA;
	pin_B = pinB;
	pin_C = pinC;
}

void RotaryEncoder::prepare()
{
	pinMode(pin_A, INPUT);
	digitalWrite(pin_A, HIGH);

	pinMode(pin_B, INPUT);
	digitalWrite(pin_B, HIGH);

	if (pin_C > 0)
	{
		pinMode(pin_C, INPUT);
		digitalWrite(pin_C, HIGH);
	}
}

// Return:
// 1: Left
// 2: Right
// 3: Button
// -1: Timeout (only returns if maxWait seconds is specified and reached)
char RotaryEncoder::getInput(int maxWait)
{
	long MaxMillis = millis() + maxWait * 1000;

	int dir_0, dir_1;

	while (true)
	{
		dir_0 = digitalRead(pin_A);
		dir_1 = digitalRead(pin_B);

		while (dir_0 + dir_1 < 2) // No neutro
		{
			dir_0 = digitalRead(pin_A);
			dir_1 = digitalRead(pin_B);
		}

		while (dir_0 + dir_1 == 2) // Neutro
		{
			dir_0 = digitalRead(pin_A);
			dir_1 = digitalRead(pin_B);

			if (pin_C > 0)
				if (!digitalRead(pin_C))
				{
					while (!digitalRead(pin_C)) { delay(10); }
					return 3;
				}

			if (maxWait > -1)
				if (MaxMillis < millis()) return -1; // TIMEOUT
		}

		if (dir_0 == 1 && dir_1 == 0)
		{
			dir_0 = digitalRead(pin_A);
			dir_1 = digitalRead(pin_B);

			while (dir_0 == 1 && dir_1 == 0)
			{
				dir_0 = digitalRead(pin_A);
				dir_1 = digitalRead(pin_B);
			}

			if (dir_0 == 0 && dir_1 == 0)
			{
				return 1;
			}
		}
		else if (dir_0 == 0 && dir_1 == 1)
		{
			dir_0 = digitalRead(pin_A);
			dir_1 = digitalRead(pin_B);

			while (dir_0 == 0 && dir_1 == 1)
			{
				dir_0 = digitalRead(pin_A);
				dir_1 = digitalRead(pin_B);
			}

			if (dir_0 == 0 && dir_1 == 0)
			{
				return 2;
			}
		}
	}
}

char RotaryEncoder::getInput()
{
	return getInput(-1);
}
