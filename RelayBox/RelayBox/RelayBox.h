#include "ClassNames.h"
#include HEADER_FILE(DALLAS_TEMPERATURE_CLASS)

#include "RelayBoxServer.h"
#include "NtpServerTime.h"
#include "Ldr.h"
#include "PirMotionSensor.h"
#include "FourChannelRelayModule.h"
#include "Buzzer.h"

class RelayBox
{
public:
	RelayBox();
	void setup();

	void loop();

	NtpServerTime& GetTime();
	DallasTemperature& GetTempSensor(); // TODO Change to app specific Temperature
	Ldr& GetLdr();
	PirMotionSensor& GetPirMotionSensor();
	FourChannelRelayModule& GetFourChannelRelayModule();
	
private:
	RelayBoxServer _server;
	NtpServerTime _time;
	Ldr _ldr;
	DallasTemperature _tempSensors;
	PirMotionSensor _pirMotionSensor;
	FourChannelRelayModule _fourChannelRelayModule;
	Buzzer _buzzer;
};