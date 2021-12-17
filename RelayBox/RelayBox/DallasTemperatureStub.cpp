#ifdef WIN32

#include "DallasTemperatureStub.h"

DallasTemperature::DallasTemperature(OneWire* oneWire)
{
	(void)oneWire;
}


void DallasTemperature::begin()
{
}


void DallasTemperature::requestTemperatures()
{
}


float DallasTemperature::getTempCByIndex(int sensorIndex)
{
	(void)sensorIndex;
	return 127.0;
}

#endif // WIN#2