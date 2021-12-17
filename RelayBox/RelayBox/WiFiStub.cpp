#ifdef WIN32

#pragma once

#include "WiFiStub.h"


WiFiStub WiFi;


void WiFiStub::begin(const char* ssid, const char* password)
{
	(void)ssid;
	(void)password;
}


const char* WiFiStub::localIP()
{
	return "12.34.56.789";
}


int WiFiStub::status()
{
	return WL_CONNECTED;
}


// Time NTP Server

void configTime(int gmtOffsetSec, int daylightOffsetSec, const char* ntp_server)
{
	(void)gmtOffsetSec;
	(void)daylightOffsetSec;
	(void)ntp_server;

}


bool getLocalTime(struct tm* timeInfo)
{
	(void)timeInfo;
	return true;
}

#endif // WIN32