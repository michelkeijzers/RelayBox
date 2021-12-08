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
}


void AsyncWebServer::begin()
{
}


void AsyncWebServer::handleClient()
{
}

void AsyncWebServer::addHandler(AsyncWebSocket* webSocket)
{
}


//void AsyncWebServer::on(const char* input, void* function)
//{
//}


AsyncCallbackWebHandler& AsyncWebServer::on(const char* something, int httpGet, ArRequestHandlerFunction function)
{
	return _handler;
}


void AsyncWebServer::onNotFound(void* function)
{
}


void AsyncWebServer::send(int code, const char* textHtml, STRING content)
{
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

// class AsyncWebServerRequest

void AsyncWebServerRequest::send_P(int port, const char* textHmlt, STRING text, ProcessorHandlerFunction function)
{
}



// class ASyncWebSocket

AsyncWebSocket::AsyncWebSocket(const char* address)
{
}


void AsyncWebSocket::cleanupClients()
{
}


void AsyncWebSocket::onEvent(callback_function onEvent)
{
}


void AsyncWebSocket::textAll(const char* text)
{
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