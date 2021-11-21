#include "FourChannelRelayModule.h"

#include "AssertUtils.h"

FourChannelRelayModule::FourChannelRelayModule()
{

}


bool FourChannelRelayModule::GetRelayState(int index)
{
	AssertUtils::MyAssert(index >= 0);
	AssertUtils::MyAssert(index < NR_OF_RELAIS);

	return _relayStates[index];
}


void FourChannelRelayModule::SetRelayState(int index, bool state)
{
	AssertUtils::MyAssert(index >= 0);
	AssertUtils::MyAssert(index < NR_OF_RELAIS);

	_relayStates[index] = state;
}
