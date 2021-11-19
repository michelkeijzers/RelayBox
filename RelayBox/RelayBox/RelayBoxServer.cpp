#include "RelayBoxServer.h"

#include "ClassNames.h"
#include HEADER_FILE(WEB_SERVER_CLASS)
#include "HtmlComposer.h"


WebServer server(80);

ServerData RelayBoxServer::_serverData;


RelayBoxServer::RelayBoxServer()
{
}


RelayBoxServer::~RelayBoxServer()
{
}


void RelayBoxServer::Setup()
{
    server.begin();
    Serial.println("HTTP server started");
}


void RelayBoxServer::HandleClient()
{
    server.handleClient();
}



/* static */ ServerData& RelayBoxServer::GetServerData()
{
    return _serverData;
}


/* static */ void RelayBoxServer::Send(int code /* = 200 */)
{
    STRING text;

    switch (code)
    {
    case 200:
    {
        HtmlComposer composer(_serverData);
        composer.Compose(text);
    }
    break;

    case 404:
        text = "Not found";
        break;

    default:
        break;
    }

    Serial.println(code);
    server.send(code, "text/html", text);
}


void RelayBoxServer::SetCallbacks()
{
    server.on("/", OnConnect);
    server.on("/led1on", HandleLed1On);
    server.on("/led1off", HandleLed1Off);
    server.on("/led2on", HandleLed2On);
    server.on("/led2off", HandleLed2Off);
    server.onNotFound(HandleNotFound);
}


/* static */ void RelayBoxServer::OnConnect()
{
    _serverData.SetLed1Status(LOW);
    _serverData.SetLed2Status(LOW);
    Serial.println("LED1 and LED2: OFF");

    Send();
}


/* static */ void RelayBoxServer::HandleLed1On()
{
    if (_serverData.GetLed1Status() == LOW)
    {
        _serverData.SetLed1Status(HIGH);
        Serial.println("LED1: ON");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed1Off()
{
    if (_serverData.GetLed1Status() == HIGH)
    {
        _serverData.SetLed1Status(LOW);
        Serial.println("LED1: OFF");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed2On()
{
    if (_serverData.GetLed2Status() == LOW)
    {
        _serverData.SetLed2Status(HIGH);
        Serial.println("LED2: ON");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed2Off()
{
    if (_serverData.GetLed2Status() == HIGH)
    {
        _serverData.SetLed2Status(LOW);
        Serial.println("LED2: OFF");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleNotFound()
{
    Send(404);
}
