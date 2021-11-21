#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


constexpr auto NR_OF_RELAIS = 4;


class FourChannelRelayModule
{
public:
	FourChannelRelayModule();

	void Setup(uint8_t pin1, uint8_t pin2, uint8_t pin3, uint8_t pin4);

	bool GetRelayState(int index);

	void SetRelayState(int index, bool state);

	void Update();

private:
	uint8_t _pins[NR_OF_RELAIS];
	bool _relayStates[NR_OF_RELAIS];
};

