#ifdef WIN32

#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)

#include <functional>

class AsyncWebSocket;

#define WS_EVT_CONNECT		0
#define WS_EVT_DISCONNECT	1
#define WS_EVT_DATA			2
#define WS_EVT_PONG			3
#define WS_EVT_ERROR		4

#define HTTP_GET           100


class AsyncWebServerRequest;

typedef std::function<void(AsyncWebServerRequest* request)> ArRequestHandlerFunction;


class AsyncCallbackWebHandler
{
public:
	AsyncCallbackWebHandler();
};


class AsyncWebServer
{
public:
	AsyncWebServer(int port);

	void begin();

	void handleClient();

	void addHandler(AsyncWebSocket* webSocket);

	// void on(const char* input, void* function);

	AsyncCallbackWebHandler& on(const char* something, int httpGet, ArRequestHandlerFunction function);
	//AsyncCallbackWebHandler& on(const char* something, int httpGet, int function);

	void onNotFound(void* function);

	void send(int code, const char* textHtml, STRING content);
};



typedef std::function<void(const STRING& text)> ProcessorHandlerFunction;

class AsyncWebServerRequest
{
public:
	void send_P(int port, const char* textHmlt, STRING text, ProcessorHandlerFunction function);
};


class AsyncWebSocketClient
{
public:
	AsyncWebSocketClient();

	void id();
	void remoteIP();
};


typedef int AwsEventType;

typedef void (*callback_function)(AsyncWebSocket* server, AsyncWebSocketClient* client, AwsEventType type, void* arg, uint8_t* data, size_t len);


class AsyncWebSocket
{
public:
	AsyncWebSocket(const char* address);

	void cleanupClients();

	void onEvent(callback_function onEvent);

	void textAll(const char* text);
};


#define WS_TEXT 0

class AwsFrameInfo
{
public:
	AwsFrameInfo();

public:
	int final;
	int index;
	int len;
	int opcode;
};


#endif
