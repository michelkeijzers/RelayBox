#ifdef WIN32

#include "DallasTemperatureStub.h"

DallasTemperature::DallasTemperature(OneWire* oneWire)
{
}


DallasTemperature::~DallasTemperature()
{
}


void DallasTemperature::begin()
{
}


void DallasTemperature::requestTemperatures()
{
}


float DallasTemperature::getTempCByIndex(int sensorIndex)
{
	return 127.0;
}

#endif // WIN#2