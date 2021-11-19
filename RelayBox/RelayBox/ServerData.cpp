#include "ServerData.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)


ServerData::ServerData()
	: _ldrSensorValue(0),
	  _temperature(0.0f),
	  _led1Status(LOW),
	  _led2Status(LOW),
	  _pirMotionSensorMotionDetected(false),
	  _time("")
{
}


ServerData::~ServerData()
{
}


bool ServerData::GetLed1Status()
{
	return _led1Status;
}


void ServerData::SetLed1Status(bool status)
{
	_led1Status = status;
}


bool ServerData::GetLed2Status()
{
	return _led2Status;
}


void ServerData::SetLed2Status(bool status)
{
	_led2Status = status;
}


float ServerData::GetTemperature()
{
	return _temperature;
}


void ServerData::SetTemperature(float value)
{
	_temperature = value;
}


int ServerData::GetLdrSensorValue()
{
	return _ldrSensorValue;
}


void ServerData::SetLdrSensorValue(int value)
{
	_ldrSensorValue = value;
}


bool ServerData::IsPirMotionSensorMotionDetected()
{
	return _pirMotionSensorMotionDetected;
}


void ServerData::SetPirMotionSensorMotionDetected(bool status)
{
	_pirMotionSensorMotionDetected = status;
}


const char* ServerData::GetTime()
{
	return _time;
}


void ServerData::SetTime(const char* time)
{
	_time = time;
}
