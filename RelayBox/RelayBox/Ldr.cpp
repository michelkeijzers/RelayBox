#include "Ldr.h"

Ldr::Ldr(uint8_t pin)
:_pin(pin),
 _ldrValue(0)
{
}


void Ldr::Update()
{
	_ldrValue = analogRead(_pin);
}


int Ldr::GetLdrValue()
{
	return _ldrValue;
}


