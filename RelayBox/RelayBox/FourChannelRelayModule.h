#pragma once


constexpr auto NR_OF_RELAIS = 4;


class FourChannelRelayModule
{
public:
	FourChannelRelayModule();

	bool GetRelayState(int index);

	void SetRelayState(int index, bool state);

private:
	bool _relayStates[NR_OF_RELAIS];
};

