#include "RelayBoxServer.h"
#include "RelayBox.h"

#include "ClassNames.h"
#include HEADER_FILE(WEB_SERVER_CLASS)
#include "HtmlComposer.h"


WebServer server(80);

/* static */ RelayBox* RelayBoxServer::_relayBox = NULL;


RelayBoxServer::RelayBoxServer()
{
}


/* static */ void RelayBoxServer::SetRelayBox(RelayBox* relayBox)
{
    _relayBox = relayBox;
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


/* static */ void RelayBoxServer::Send(int code /* = 200 */)
{
    STRING text;

    switch (code)
    {
    case 200:
    {
        HtmlComposer composer(_relayBox);
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
    _relayBox->GetFourChannelRelayModule().SetRelayState(0, LOW);
    _relayBox->GetFourChannelRelayModule().SetRelayState(1, LOW);
    Serial.println("LED1 and LED2: OFF");

    Send();
}


/* static */ void RelayBoxServer::HandleLed1On()
{
    if (_relayBox->GetFourChannelRelayModule().GetRelayState(0) == LOW)
    {
        _relayBox->GetFourChannelRelayModule().SetRelayState(0, HIGH);
        Serial.println("LED1: ON");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed1Off()
{
    if (_relayBox->GetFourChannelRelayModule().GetRelayState(0) == HIGH)
    {
        _relayBox->GetFourChannelRelayModule().SetRelayState(0, LOW);
        Serial.println("LED1: OFF");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed2On()
{
    if (_relayBox->GetFourChannelRelayModule().GetRelayState(1) == LOW)
    {
        _relayBox->GetFourChannelRelayModule().SetRelayState(1, HIGH);
        Serial.println("LED2: ON");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed2Off()
{
    if (_relayBox->GetFourChannelRelayModule().GetRelayState(1) == HIGH)
    {
        _relayBox->GetFourChannelRelayModule().SetRelayState(1, LOW);
        Serial.println("LED2: OFF");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleNotFound()
{
    Send(404);
}
