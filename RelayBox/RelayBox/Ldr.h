#pragma once


#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class Ldr
{
public:
	Ldr(uint8_t pin);

	int GetLdrValue();
	void Update();

private:
	uint8_t _pin;

	int _ldrValue;
};


