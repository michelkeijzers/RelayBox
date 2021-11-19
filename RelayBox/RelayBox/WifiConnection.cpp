#include "WifiConnection.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(WIFI_CLASS)


const char* ssid = "Ziggo41066";
const char* password = "tc7KK4P6FFEF";


WifiConnection::WifiConnection()
{
}


WifiConnection::~WifiConnection()
{
}


void WifiConnection::Connect()
{
    Serial.println("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    //check wi-fi is connected to wi-fi network
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected..!");
    Serial.print("Got IP: ");
    Serial.println(WiFi.localIP());
}