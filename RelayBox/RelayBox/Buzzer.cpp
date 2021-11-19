#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

#include "Buzzer.h"

Buzzer::Buzzer()
	: _pin(255)
{
}


Buzzer::~Buzzer()
{
}


void Buzzer::Setup(int pin)
{
	_pin = pin;
	ledcSetup(LED_CHANNEL, FREQUENCY, RESOLUTION);
	ledcAttachPin(pin, LED_CHANNEL);
}


void Buzzer::Play(float frequency)
{
	ledcWriteTone(LED_CHANNEL, frequency);
}


void Buzzer::PlayWait(float frequency, int durationMs)
{
	Play(frequency);
	delay(durationMs);
	Stop();
}


void Buzzer::Stop()
{
	ledcWriteTone(LED_CHANNEL, 0);
}
