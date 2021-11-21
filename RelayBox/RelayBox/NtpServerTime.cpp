#include "NtpServerTime.h"
#include "time.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(WIFI_CLASS)


NtpServerTime::NtpServerTime()
{
    strcpy_s(_timeContent, "");
}


void NtpServerTime::Setup()
{
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
}

void NtpServerTime::Receive()
{
    struct tm timeInfo;

    if (!getLocalTime(&timeInfo))
    {
        strcpy_s(_timeContent, "Failed to obtain time");
        return;
    }

    sprintf_s(_timeContent, "Day %d of the week, %04d-%02d-%02d %02d:%02d:%02d (daylight saving time: %d, day %d of this year)",
        timeInfo.tm_wday, timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
        timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec, timeInfo.tm_isdst, timeInfo.tm_yday);
}


const char* NtpServerTime::TimeAsString()
{
    return _timeContent;
}