#include "HtmlComposer.h"

HtmlComposer::HtmlComposer(ServerData& serverData)
: _serverData(serverData)
{
}


HtmlComposer::~HtmlComposer()
{
}


void HtmlComposer::Compose(STRING& ptr)
{
    ptr = "<!DOCTYPE html> <html>\n";
    ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
    ptr += "<meta http-equiv=\"refresh\" content=\"1\">";
    ptr += "<title>LED Control</title>\n";
    ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
    ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
    ptr += ".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
    ptr += ".button-on {background-color: #3498db;}\n";
    ptr += ".button-on:active {background-color: #2980b9;}\n";
    ptr += ".button-off {background-color: #34495e;}\n";
    ptr += ".button-off:active {background-color: #2c3e50;}\n";
    ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
    ptr += "</style>\n";
    ptr += "</head>\n";
    ptr += "<body>\n";
    ptr += "<h1>ESP32 Relay Box</h1>\n";

    Serial.print("LED1 state:");
    Serial.print(_serverData.GetLed1Status());
    Serial.print(", LED2 state:");
    Serial.println(_serverData.GetLed2Status());


    if (_serverData.GetLed1Status())
    {
        ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
    }
    else
    {
        ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
    }

    if (_serverData.GetLed2Status())
    {
        ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
    }
    else
    {
        ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";
    }

    char buffer[256];

    //Serial.print("  Sensor data: ");
    //Serial.println(_serverData.GetLdrSensorValue());
    ptr += "<p>LDR value: ";
    sprintf_s(buffer, "%d", _serverData.GetLdrSensorValue());
    ptr += buffer;
    ptr += "</p>";

    //Serial.print("  Current Date/Time: ");
    //Serial.println(_serverData.GetTime());
    ptr += "<p>Current Date/Time: ";
    sprintf_s(buffer, "%s", _serverData.GetTime());
    ptr += buffer;
    ptr += "</p>";

    //Serial.print("  Temperature: ");
    //Serial.println(_serverData.GetTemperature());
    ptr += "<p>Temperature: ";
    sprintf_s(buffer, "%.1f", _serverData.GetTemperature());
    ptr += buffer;
    ptr += "</p>";

    //Serial.print("  Motion sensor: ");
    //Serial.println(_serverData.IsPirMotionSensorMotionDetected());
    ptr += "<p>PIR Motion Sensor: ";
    if (_serverData.PirMotionSensorSecondsUntilInitialized() == 0)
    {
        if (_serverData.IsPirMotionSensorMotionDetected())
        {
            ptr += "Motion Detected";
        }
        else
        {
            ptr += "No Motion";
        }
    }
    else
    {
        sprintf_s(buffer, "Initializing for %d s", _serverData.PirMotionSensorSecondsUntilInitialized());
        ptr += buffer;
    }

    ptr += "</p>";

    ptr += "</body>\n";
    ptr += "</html>\n";
}
