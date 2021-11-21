#include "ClassNames.h"
#include HEADER_FILE(DALLAS_TEMPERATURE_CLASS)

#include "PirMotionSensor.h"
#include "Buzzer.h"
#include "NtpServerTime.h"
#include "FourChannelRelayModule.h"
#include "Ldr.h"
#include "RelayBoxServer.h"

class RelayBox
{
public:
	RelayBox();

	void setup();

	void loop();

	NtpServerTime& GetTime();

	DallasTemperature& GetTempSensor(); // TODO Change to app specific Temperature

	PirMotionSensor& GetPirMotionSensor();

	Ldr& GetLdr();

	FourChannelRelayModule& GetFourChannelRelayModule();

private:
	RelayBoxServer _server;
	NtpServerTime _time;
	DallasTemperature _tempSensors;
	PirMotionSensor _pirMotionSensor;
	Ldr _ldr;
	FourChannelRelayModule _fourChannelRelayModule;
	Buzzer _buzzer;
};