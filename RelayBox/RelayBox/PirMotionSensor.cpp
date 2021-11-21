#include "PirMotionSensor.h"

#include "MathUtils.h"

const int INITIALIZATION_TIME = 60 * 1000;


PirMotionSensor::PirMotionSensor()
	: _secondsUntilInitialized((INITIALIZATION_TIME + 999) / 1000),
	  _isMotionDetected(false),
	  _pin(255)
{
}


void PirMotionSensor::Setup(int pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}


void PirMotionSensor::Update()
{
	if (_secondsUntilInitialized == 0)
	{
		_isMotionDetected = (digitalRead(_pin) == HIGH);
	}
	else
	{
		_secondsUntilInitialized = MathUtils::Max(0, INITIALIZATION_TIME - millis() + 999) / 1000;
	}
}


int PirMotionSensor::SecondsUntilInitialized()
{
	return _secondsUntilInitialized;
}


bool PirMotionSensor::IsMotionDetected()
{
	return _isMotionDetected;
}
