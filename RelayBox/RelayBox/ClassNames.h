// ClassNames.h

#pragma once

// Used to include variable class names
#define stringify(x) #x
#define HEADER_FILE(a) stringify(a.h)

#ifndef WIN32
#define STRING String
#endif


// Class names
#ifdef WIN32

#define ARDUINO_CLASS				ArduinoStub
#define SERIAL_CLASS				SerialStub
#define WIFI_CLASS                  WiFiStub
#define WEB_SERVER_CLASS            WebServerStub
#define ONE_WIRE_CLASS              OneWireStub
#define DALLAS_TEMPERATURE_CLASS    DallasTemperatureStub

#else // NON _WINDOWS

#define strcpy_s(d,d_sz,s)			strcpy(d, s);
#define strcpy_s(d, s)				strcpy(d, s)
#define sprintf_s                   sprintf

#define ABS							abs
#define MIN(a,b)					(((a)<(b))?(a):(b))
#define MAX(a,b)					(((a)>(b))?(a):(b))
#define FastLedCRGB					CRGB

#define ARDUINO_CLASS				Arduino
#define SERIAL_CLASS				Arduino
#define WIFI_CLASS                  WiFi
#define WEB_SERVER_CLASS            WebServer
#define ONE_WIRE_CLASS              OneWire
#define DALLAS_TEMPERATURE_CLASS    DallasTemperature

#endif // _WINDOWS
