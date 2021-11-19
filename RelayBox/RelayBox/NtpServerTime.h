// https://microcontrollerslab.com/getting-current-date-time-esp32-arduino-ide-ntp-server/

#pragma once

constexpr auto MAX_TIME_CONTENT_SIZE = 256;

class NtpServerTime
{
public:
	NtpServerTime();
	~NtpServerTime();

	void Setup();

	void Receive();

	const char* TimeAsString();

private:
	// Time
	const char* NTP_SERVER				= "pool.ntp.org";
	const long  GMT_OFFSET_SEC			=    0;
	const int   DAYLIGHT_OFFSET_SEC		= 3600;
	char _timeContent[MAX_TIME_CONTENT_SIZE];
};

