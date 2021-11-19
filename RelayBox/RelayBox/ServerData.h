#pragma once
class ServerData
{
public:
	ServerData();

	~ServerData();

	bool GetLed1Status();
	void SetLed1Status(bool status);
	
	bool GetLed2Status();
	void SetLed2Status(bool status);

	float GetTemperature();
	void SetTemperature(float value);

	int GetLdrSensorValue();
	void SetLdrSensorValue(int value);
	
	bool IsPirMotionSensorMotionDetected();
	void SetPirMotionSensorMotionDetected(bool status);

	const char* GetTime();
	void SetTime(const char* time);
	
private:
	bool _led1Status;
	bool _led2Status;
	float _temperature;
	int _ldrSensorValue;
	bool _pirMotionSensorMotionDetected;
	const char* _time;
};

