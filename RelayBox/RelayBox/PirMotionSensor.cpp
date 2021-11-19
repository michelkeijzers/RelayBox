#include "PirMotionSensor.h"



PirMotionSensor::PirMotionSensor()
	: _pin(255)
{
}


PirMotionSensor::~PirMotionSensor()
{
}


void PirMotionSensor::Setup(int pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}


bool PirMotionSensor::IsMotionDetected()
{
	return digitalRead(_pin) == HIGH;
}