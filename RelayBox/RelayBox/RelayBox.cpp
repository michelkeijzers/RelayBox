// Pins of ESP32                        https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
// Client Address of Web Server         http://192.168.178.14/led2off
// Over The Air (OTA) Programming       https://lastminuteengineers.com/esp8266-ota-updates-arduino-ide/
// Gas Sensor MQ2                       https://diyi0t.com/mq2-gas-sensor-arduino-esp8266-esp32/
// Sound sensor KY-038 / KY-037 / LD393 https://diyi0t.com/sound-sensor-arduino-esp8266-esp32/

#include "RelayBox.h"
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(ONE_WIRE_CLASS)
#include HEADER_FILE(DALLAS_TEMPERATURE_CLASS)

#include "WifiConnection.h"
#include "RelayBoxServer.h"
#include "HtmlComposer.h"

// DS18B20
const int ONE_WIRE_BUS = 4; // TODO
OneWire _oneWire(ONE_WIRE_BUS);

const uint8_t PIN_LDR = A0;
const uint8_t PIN_PIR_MOTION_SENSOR = 39;
const uint8_t PIN_RELAY_1 = 4;
const uint8_t PIN_RELAY_2 = 5;
const uint8_t PIN_RELAY_3 = 18;
const uint8_t PIN_RELAY_4 = 19;
const uint8_t PIN_BUZZER = 32;

long _lastUpdate = millis();

WifiConnection _wifiConnection;



RelayBox::RelayBox()
: _ldr(PIN_LDR),
  _tempSensors(&_oneWire)
{
    _server.SetRelayBox(this);
}


void RelayBox::setup()
{
    Serial.begin(115200);
    _wifiConnection.Connect();
    _server.InitWebSocket();

    _server.Send();
    _server.Begin();
    //_server.SetCallbacks();
    _time.Setup();
    _tempSensors.begin(); // TODO : change to setup and specific class
    _pirMotionSensor.Setup(PIN_PIR_MOTION_SENSOR);
    _fourChannelRelayModule.Setup(PIN_RELAY_1, PIN_RELAY_2, PIN_RELAY_3, PIN_RELAY_4);
    _buzzer.Setup(PIN_BUZZER);
}

void RelayBox::loop()
{
    //_server.HandleClient();

    if (millis() - _lastUpdate > 1000) // TODO: Or when LED changed (led button pressed on website)
    {
        Serial.println("Update");
        _lastUpdate = millis();
        _ldr.Update();
        _time.Update();
        _tempSensors.requestTemperatures(); // Takes quite some time
        _pirMotionSensor.Update();
        _fourChannelRelayModule.Update();
        _server.Send();

        _server.CleanupClients();
    }
}


NtpServerTime& RelayBox::GetTime()
{
    return _time;
}


DallasTemperature& RelayBox::GetTempSensor()
{
    return _tempSensors;
}


PirMotionSensor& RelayBox::GetPirMotionSensor()
{
    return _pirMotionSensor;
}


FourChannelRelayModule& RelayBox::GetFourChannelRelayModule()
{
    return _fourChannelRelayModule;
}


Ldr& RelayBox::GetLdr()
{
    return _ldr;
}