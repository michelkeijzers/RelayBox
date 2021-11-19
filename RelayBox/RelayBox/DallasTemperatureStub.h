#ifdef WIN32

#pragma once

#include "ClassNames.h"
#include HEADER_FILE(ONE_WIRE_CLASS)

class DallasTemperature
{
public:
	DallasTemperature(OneWire* oneWire);

	~DallasTemperature();

	void begin();

	void requestTemperatures();
	
	float getTempCByIndex(int sensorIndex);
};

#endif // WIN32