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

#include "PirMotionSensor.h"
#include "Buzzer.h"
#include "NtpServerTime.h"
#include "WifiConnection.h"
#include "RelayBoxServer.h"

// DS18B20
const int ONE_WIRE_BUS = 4; // TODO
OneWire _oneWire(ONE_WIRE_BUS);
DallasTemperature _tempSensors(&_oneWire);

const uint8_t PIN_LED_1 = 4;
const uint8_t PIN_LED_2 = 5;
const uint8_t PIN_BUZZER = 32;
const uint8_t PIN_PIR_MOTION_SENSOR = 39;
const uint8_t PIN_LDR = A0;

RelayBoxServer _server;
WifiConnection _wifiConnection;
NtpServerTime _time;
PirMotionSensor _pirMotionSensor;
Buzzer _buzzer;
long _lastUpdate = millis();


RelayBox::RelayBox()
{
}


RelayBox::~RelayBox()
{
}


void RelayBox::setup()
{
    Serial.begin(115200);
    pinMode(PIN_LED_1, OUTPUT);
    pinMode(PIN_LED_2, OUTPUT);
    _buzzer.Setup(PIN_BUZZER);
    _wifiConnection.Connect();
    _time.Setup();
    _time.Receive();
    _pirMotionSensor.Setup(PIN_PIR_MOTION_SENSOR);
    _tempSensors.begin();
    _buzzer.PlayWait(440.0, 100);
    _server.SetCallbacks();
    _server.Setup();
}

void RelayBox::loop()
{
    ServerData& serverData = _server.GetServerData();

    _server.HandleClient();

    //TODO Move to RelayModule
    digitalWrite(PIN_LED_1, serverData.GetLed1Status());
    digitalWrite(PIN_LED_2, serverData.GetLed2Status());

    if (millis() - _lastUpdate > 1000) // TODO: Or when LED changed (led button pressed on website)
    {
        _lastUpdate = millis();
        serverData.SetLdrSensorValue(analogRead(PIN_LDR));
        _tempSensors.requestTemperatures(); // Takes quite some time
        serverData.SetTemperature(_tempSensors.getTempCByIndex(0));

        // Set to MotionDetector
        _pirMotionSensor.Update();
        serverData.SetPirMotionSensorData(_pirMotionSensor.SecondsUntilInitialized(), _pirMotionSensor.IsMotionDetected());
        
        _time.Receive();
        serverData.SetTime(_time.TimeAsString());
        Serial.println("UpdateHTML");
        _server.Send(200, _server.ComposeHtml());
    }
}
