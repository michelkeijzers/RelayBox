#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(ESP_ASYNC_WEB_SERVER_CLASS)

class RelayBox;
class AsyncWebSocket;
class AsyncWebSocketClient;

class RelayBoxServer
{
public:
	RelayBoxServer();
	static void SetRelayBox(RelayBox* relayBox);


	// NEW
	static void InitWebSocket();
	void Begin();
	static void Send(int code = 200);
	static STRING Processor(const STRING& var);
	void CleanupClients();

	static void NotifyClients();
	static void HandleWebSocketMessage(void* arg, uint8_t* data, size_t len);
	static void OnEvent(/*AsyncWebSocket* server, */ AsyncWebSocketClient* client, AwsEventType type,
		void* arg, uint8_t* data, size_t len);


private:
	static void OnConnect();
	static void HandleLed1On();
	static void HandleLed1Off();
	static void HandleLed2On();
	static void HandleLed2Off();
	static void HandleNotFound();

	static RelayBox* _relayBox;
};
