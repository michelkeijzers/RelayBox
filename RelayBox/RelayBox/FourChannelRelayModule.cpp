#include "FourChannelRelayModule.h"

#include "AssertUtils.h"

FourChannelRelayModule::FourChannelRelayModule()
	: _pins { 0, 0, 0, 0 },
	  _relayStates { LOW, LOW, LOW, LOW} 
{
}


void FourChannelRelayModule::Setup(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4)
{
	_pins[0] = pin1;
	_pins[1] = pin2;
	_pins[2] = pin3;
	_pins[3] = pin4;

	for (uint8_t pin = 0; pin < NR_OF_RELAIS; pin++)
	{
		pinMode(_pins[pin], OUTPUT);
		digitalWrite(_pins[pin], LOW);
	}
}


bool FourChannelRelayModule::GetRelayState(int index)
{
	AssertUtils::MyAssert(index >= 0);
	AssertUtils::MyAssert(index < NR_OF_RELAIS);

	if ((index >= 0) && (index < NR_OF_RELAIS))
	{
		return _relayStates[index];
	}

	return false;
}


void FourChannelRelayModule::SetRelayState(int index, bool state)
{
	AssertUtils::MyAssert(index >= 0);
	AssertUtils::MyAssert(index < NR_OF_RELAIS);

	if ((index >= 0) && (index < NR_OF_RELAIS))
	{
		_relayStates[index] = state;
	}
}


void FourChannelRelayModule::Update()
{
	for (uint8_t relay = 0; relay < NR_OF_RELAIS; relay++)
	{
		digitalWrite(_pins[relay], _relayStates[relay]);
	}
}