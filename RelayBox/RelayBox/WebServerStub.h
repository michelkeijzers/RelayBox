#ifdef WIN32

#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


class WebServer
{
public:
	WebServer(int port);

	void begin();

	void handleClient();

	void on(const char* input, void* function);

	void onNotFound(void* function);

	void send(int code, const char* textHtml, STRING content);
};

#endif // WIN32