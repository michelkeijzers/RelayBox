#ifdef WIN32

#include "WebServerStub.h"

WebServer::WebServer(int port)
{
}


void WebServer::begin()
{
}


void WebServer::handleClient()
{
}


void WebServer::on(const char* input, void* function)
{
}


void WebServer::onNotFound(void* function)
{
}


void WebServer::send(int code, const char* textHtml, STRING content)
{
}

#endif // WIN32