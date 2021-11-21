// https://diyi0t.com/hc-sr501-pir-motion-sensor-arduino-esp8266-esp32/

#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

class PirMotionSensor
{
public:
	PirMotionSensor();
	void Setup(int pin);

	void Update();
	int SecondsUntilInitialized();
	bool IsMotionDetected();

private:
	uint8_t _pin;

	int _secondsUntilInitialized;

	bool _isMotionDetected;
};

