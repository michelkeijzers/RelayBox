#ifdef WIN32

#include "WebServerStub.h"

WebServer::WebServer(int port)
{
	(void)port;
}


void WebServer::begin()
{
}


void WebServer::handleClient()
{
}


void WebServer::on(const char* input, void* function)
{
	(void)input;
	(void)function;
}


void WebServer::onNotFound(void* function)
{
	(void)function;
}


void WebServer::send(int code, const char* textHtml, STRING content)
{
	(void)code;
	(void)textHtml;
	(void)content;
}

#endif // WIN32