#include "RelayBox.h"

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-async-web-server-espasyncwebserver-library/
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// Import required libraries
#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(ASYNC_TCP_CLASS)
//#include HEADER_FILE(WEB_SERVER_CLASS)
#include HEADER_FILE(ESP_ASYNC_WEB_SERVER_CLASS)

// Replace with your network credentials
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
</html>
)rawliteral";


RelayBox::RelayBox()
{
}

STRING outputState(int8_t output) {
    if (digitalRead(output)) {
        return "checked";
    }
    else {
        return "";
    }
}

// Replaces placeholder with button section in your web page
STRING processor(const STRING& var) {
    //Serial.println(var);
    if (var == "BUTTONPLACEHOLDER") {
        STRING buttons = "";
        buttons += "<h4>Output - GPIO 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(2) + "><span class=\"slider\"></span></label>";
        buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"4\" " + outputState(4) + "><span class=\"slider\"></span></label>";
        buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"33\" " + outputState(33) + "><span class=\"slider\"></span></label>";
        return buttons;
    }
    return STRING();
}


void RelayBox::setup() {
    // Serial port for debugging purposes
    Serial.begin(115200);

    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    pinMode(33, OUTPUT);
    digitalWrite(33, LOW);

    // Connect to Wi-Fi
    /*WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
        }
    */

    _wifiConnection.Connect();

    // Print ESP Local IP Address
    Serial.println(WiFi.localIP());

    // Route for root / web page
#ifndef WIN32
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", index_html, processor);
        });
#endif

    // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
        STRING inputMessage1;
        STRING inputMessage2;
        // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
        if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
            inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
            inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
            digitalWrite((uint8_t) inputMessage1.toInt(), inputMessage2.toInt());
        }
        else {
            inputMessage1 = "No message sent";
            inputMessage2 = "No message sent";
        }
        Serial.print("GPIO: ");
        Serial.print(inputMessage1);
        Serial.print(" - Set to: ");
        Serial.println(inputMessage2);
        request->send(200, "text/plain", "OK");
        });

    // Start server
    server.begin();
}

void RelayBox::loop()
{
}

//// Pins of ESP32                        https://randomnerdtutorials.com/esp32-pinout-reference-gpios/
//// Client Address of Web Server         http://192.168.178.14/led2off
//// Over The Air (OTA) Programming       https://lastminuteengineers.com/esp8266-ota-updates-arduino-ide/
//// Gas Sensor MQ2                       https://diyi0t.com/mq2-gas-sensor-arduino-esp8266-esp32/
//// Sound sensor KY-038 / KY-037 / LD393 https://diyi0t.com/sound-sensor-arduino-esp8266-esp32/
//
//#include "RelayBox.h"
//#include "ClassNames.h"
//#include HEADER_FILE(ARDUINO_CLASS)
//#include HEADER_FILE(ONE_WIRE_CLASS)
//#include HEADER_FILE(DALLAS_TEMPERATURE_CLASS)
//
//#include "WifiConnection.h"
//#include "RelayBoxServer.h"
//#include "HtmlComposer.h"
//
//// DS18B20
//const int ONE_WIRE_BUS = 4; // TODO
//OneWire _oneWire(ONE_WIRE_BUS);
//
//const uint8_t PIN_LDR = A0;
//const uint8_t PIN_PIR_MOTION_SENSOR = 39;
//const uint8_t PIN_RELAY_1 = 4;
//const uint8_t PIN_RELAY_2 = 5;
//const uint8_t PIN_RELAY_3 = 18;
//const uint8_t PIN_RELAY_4 = 19;
//const uint8_t PIN_BUZZER = 32;
//
//long _lastUpdate = millis();
//
//WifiConnection _wifiConnection;
//
//
//
//RelayBox::RelayBox()
//: _ldr(PIN_LDR),
//  _tempSensors(&_oneWire)
//{
//    _server.SetRelayBox(this);
//}
//
//
//void RelayBox::setup()
//{
//    Serial.begin(115200);
//    _wifiConnection.Connect();
//    _server.InitWebSocket();
//
//    _server.Send();
//    _server.Begin();
//    //_server.SetCallbacks();
//    _time.Setup();
//    _tempSensors.begin(); // TODO : change to setup and specific class
//    _pirMotionSensor.Setup(PIN_PIR_MOTION_SENSOR);
//    _fourChannelRelayModule.Setup(PIN_RELAY_1, PIN_RELAY_2, PIN_RELAY_3, PIN_RELAY_4);
//    _buzzer.Setup(PIN_BUZZER);
//}
//
//void RelayBox::loop()
//{
//    //_server.HandleClient();
//
//    if (millis() - _lastUpdate > 1000) // TODO: Or when LED changed (led button pressed on website)
//    {
//        Serial.println("Update");
//        _lastUpdate = millis();
//        _ldr.Update();
//        _time.Update();
//        _tempSensors.requestTemperatures(); // Takes quite some time
//        _pirMotionSensor.Update();
//        _fourChannelRelayModule.Update();
//        _server.Send();
//
//        _server.CleanupClients();
//    }
//}
//
//
//NtpServerTime& RelayBox::GetTime()
//{
//    return _time;
//}
//
//
//DallasTemperature& RelayBox::GetTempSensor()
//{
//    return _tempSensors;
//}
//
//
//PirMotionSensor& RelayBox::GetPirMotionSensor()
//{
//    return _pirMotionSensor;
//}
//
//
//FourChannelRelayModule& RelayBox::GetFourChannelRelayModule()
//{
//    return _fourChannelRelayModule;
//}
//
//
//Ldr& RelayBox::GetLdr()
//{
//    return _ldr;
//}