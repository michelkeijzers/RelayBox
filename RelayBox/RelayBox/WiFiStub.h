#ifdef WIN32

#pragma once

#include <ctime>

const int WL_CONNECTED = 1;

class WiFiStub
{
public:
	void begin(const char* ssid, const char* password);


	const char* localIP();

	int status();
};

extern WiFiStub WiFi;


// Time NTP server functions

void configTime(int gmtOffsetSec, int daylightOffsetSec, const char* ntp_server);

bool getLocalTime(struct tm* timeInfo);

#endif //WIN32