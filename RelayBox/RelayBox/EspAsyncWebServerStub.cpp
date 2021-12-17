#ifdef WIN32

#include "EspAsyncWebServerStub.h"

AsyncCallbackWebHandler _handler;

// class AsyncCallbackWebHandler

AsyncCallbackWebHandler::AsyncCallbackWebHandler()
{
};


// class AsyncWebServer

AsyncWebServer::AsyncWebServer(int port)
{
	(void)port;
}


void AsyncWebServer::begin()
{
}


void AsyncWebServer::handleClient()
{
}

void AsyncWebServer::addHandler(AsyncWebSocket* webSocket)
{
	(void)webSocket;
}


//void AsyncWebServer::on(const char* input, void* function)
//{
//}


AsyncCallbackWebHandler& AsyncWebServer::on(const char* something, int httpGet, ArRequestHandlerFunction function)
{
	(void)something;
	(void)httpGet;
	(void)function;
	return _handler;
}


void AsyncWebServer::onNotFound(void* function)
{
	(void)function;
}


void AsyncWebServer::send(int code, const char* textHtml, STRING content)
{
	(void)code;
	(void)textHtml;
	(void)content;
}

// class AsyncWebSocketClient

AsyncWebSocketClient::AsyncWebSocketClient()
{
}


void AsyncWebSocketClient::id()
{
}


void AsyncWebSocketClient::remoteIP()
{
}

// class ASWSRData

STRING ASWSRData::value()
{
	return "";
};

// class AsyncWebServerRequest

void AsyncWebServerRequest::send(int port, const char* textHtml, STRING text)
{
	(void)port;
	(void)textHtml;
	(void)text;
}


void AsyncWebServerRequest::send_P(int port, const char* textHtml, STRING text, ProcessorHandlerFunction function)
{
	(void)port;
	(void)textHtml;
	(void)text;
	(void)function;
}

bool AsyncWebServerRequest::hasParam(const char* param)
{
	(void)param;

	return false;
}

ASWSRData* AsyncWebServerRequest::getParam(const char* param)
{
	(void)param;

	ASWSRData* data = new ASWSRData();
	return data;
}

// class ASyncWebSocket

AsyncWebSocket::AsyncWebSocket(const char* address)
{
	(void)address;
}


void AsyncWebSocket::cleanupClients()
{
}


void AsyncWebSocket::onEvent(callback_function onEvent)
{
	(void)onEvent;
}


void AsyncWebSocket::textAll(const char* text)
{
	(void)text;
}


// class AwsFrameInfo

AwsFrameInfo::AwsFrameInfo()
:	final(0),
	index(0),
	len(0),
	opcode(0)
{
}

#endif