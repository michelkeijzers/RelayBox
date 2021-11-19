#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

#include "ServerData.h"

class RelayBoxServer
{
public:
	RelayBoxServer();
	~RelayBoxServer();

	void SetCallbacks();

	void Setup();

	void HandleClient();

	static ServerData& GetServerData();

	static void Send(int code = 200);

private:
	static void OnConnect();
	static void HandleLed1On();
	static void HandleLed1Off();
	static void HandleLed2On();
	static void HandleLed2Off();
	static void HandleNotFound();

	static ServerData _serverData;
};
