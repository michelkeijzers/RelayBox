#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

class RelayBox;

class RelayBoxServer
{
public:
	RelayBoxServer();
	static void SetRelayBox(RelayBox* relayBox);
	void SetCallbacks();
	void Setup();

	void HandleClient();
	static void Send(int code = 200);

private:
	static void OnConnect();
	static void HandleLed1On();
	static void HandleLed1Off();
	static void HandleLed2On();
	static void HandleLed2Off();
	static void HandleNotFound();

	static RelayBox* _relayBox;
};
