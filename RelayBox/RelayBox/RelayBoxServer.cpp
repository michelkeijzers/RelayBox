#include "RelayBoxServer.h"
#include "RelayBox.h"

#include "ClassNames.h"
#include HEADER_FILE(ARDUINO_CLASS)
#include HEADER_FILE(WIFI_CLASS)
#include HEADER_FILE(ASYNC_TCP_CLASS)
//#include HEADER_FILE(WEB_SERVER_CLASS)
#include HEADER_FILE(ESP_ASYNC_WEB_SERVER_CLASS)
#include "HtmlComposer.h"


//NEWAsyncWebServer server(80);

AsyncWebSocket webSocket("/ws");

char textBuffer[1024];

/* static */ RelayBox* RelayBoxServer::_relayBox = NULL;


RelayBoxServer::RelayBoxServer()
{
}


/* static */ void RelayBoxServer::SetRelayBox(RelayBox* relayBox)
{
    _relayBox = relayBox;
}


/*
void RelayBoxServer::SetCallbacks()
{
    server.on("/", OnConnect);
    server.on("/led1on", HandleLed1On);
    server.on("/led1off", HandleLed1Off);
    server.on("/led2on", HandleLed2On);
    server.on("/led2off", HandleLed2Off);
    server.onNotFound(HandleNotFound);
}
*/

/* static */ void RelayBoxServer::OnConnect()
{
    //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(0, LOW);
    //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(1, LOW);
    Serial.println("LED1 and LED2: OFF");

    Send();
}


/* static */ void RelayBoxServer::HandleLed1On()
{
    //NEW if (_relayBox->GetFourChannelRelayModule().GetRelayState(0) == LOW)
    {
        //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(0, HIGH);
        Serial.println("LED1: ON");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed1Off()
{
    //NEW if (_relayBox->GetFourChannelRelayModule().GetRelayState(0) == HIGH)
    {
        //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(0, LOW);
        Serial.println("LED1: OFF");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed2On()
{
    //NEW if (_relayBox->GetFourChannelRelayModule().GetRelayState(1) == LOW)
    {
        //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(1, HIGH);
        Serial.println("LED2: ON");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleLed2Off()
{
    //NEW if (_relayBox->GetFourChannelRelayModule().GetRelayState(1) == HIGH)
    {
        //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(1, LOW);
        Serial.println("LED2: OFF");
        Send();
    }
}


/* static */ void RelayBoxServer::HandleNotFound()
{
    Send(404);
}



// NEW

/* static */ void RelayBoxServer::InitWebSocket()
{
    //webSocket.onEvent(OnEvent);
    //NEW server.addHandler(&webSocket);
}



void RelayBoxServer::Begin()
{
    //NEW server.begin();
    Serial.println("HTTP server started");
}


/* static */ STRING RelayBoxServer::Processor(const STRING& var)
{
    Serial.println(var.c_str()); // TODO: Remove c_str()
    if (var == "STATE") 
    {
        //NEW if (_relayBox->GetFourChannelRelayModule().GetRelayState(1)) 
        {
            return "ON";
        }
        //NEW else 
        {
            //NEW #include HEADER_FILE(ARDUINO_CLASS)return "OFF";
        }
    }
    return "";
}



/* static */ void RelayBoxServer::NotifyClients() 
{
    //NEW bool state = _relayBox->GetFourChannelRelayModule().GetRelayState(1);
    //NEW webSocket.textAll(state ? "1" : "0");
}

/* static */ void RelayBoxServer::HandleWebSocketMessage(void* arg, uint8_t* data, size_t len) {
    AwsFrameInfo* info = (AwsFrameInfo*)arg;
    if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
        data[len] = 0;
        if (strcmp((char*)data, "toggle") == 0) {
            //NEW _relayBox->GetFourChannelRelayModule().SetRelayState(1, !_relayBox->GetFourChannelRelayModule().GetRelayState(1));
            NotifyClients();
        }
    }
}

//TODO: Used? 
/* static */ void RelayBoxServer::OnEvent(/* AsyncWebSocket* server, */ AsyncWebSocketClient* client, AwsEventType type,
    void* arg, uint8_t* data, size_t len) 
{
    (void)client;

    switch (type) {
    case WS_EVT_CONNECT:
        // TODO Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
        break;
    case WS_EVT_DISCONNECT:
        //TODO Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        HandleWebSocketMessage(arg, data, len);
        break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
        break;
    }
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
            break;
        }

        case 404:
            text = "Not found";
            break;

        default:
            break;
    }

    Serial.println(code);

    text.toCharArray(textBuffer, text.length() + 1);
    //NEW server.on("/", HTTP_GET, [](AsyncWebServerRequest* request)
        //{
        //    request->send_P(200, "text/html", textBuffer, Processor);
        //});
}


void RelayBoxServer::CleanupClients()
{
    webSocket.cleanupClients();
}