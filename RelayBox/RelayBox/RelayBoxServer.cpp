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


const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";

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


RelayBoxServer::RelayBoxServer()
{
}


/* static */ void RelayBoxServer::SetRelayBox(RelayBox* relayBox)
{
    _relayBox = relayBox;
}


/* static */ STRING RelayBoxServer::OutputState(int8_t output) {
    if (digitalRead(output)) {
        return "checked";
    }
    else {
        return "";
    }
}


// Replaces placeholder with button section in your web page
/* static */ STRING RelayBoxServer::Processor(const STRING& var) {
    //Serial.println(var);
    if (var == "BUTTONPLACEHOLDER") 
    {
        STRING buttons = "";
        buttons += "<h4>Output - GPIO 2</h4><label class = \"switch\"><input type=\"checkbox\" onchange = \"toggleCheckbox(this)\" id=\"2\" " + OutputState(2) + "><span class = \"slider\"></span></label>";
        buttons += "<h4>Output - GPIO 4</h4><label class=\"switch\"><input type=\"checkbox\" onchange = \"toggleCheckbox(this)\" id=\"4\" " + OutputState(4) + "><span class = \"slider\"></span></label>";
        buttons += "<h4>Output - GPIO 33</h4><label class=\"switch\"><input type=\"checkbox\" onchange = \"toggleCheckbox(this)\" id=\"33\" " + OutputState(33) + "><span class = \"slider\"></span></label>";
        return buttons;
    }
    return STRING();
}


void RelayBoxServer::Begin()
{
    // Route for root / web page
    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->send_P(200, "text/html", index_html, Processor);
        });

    // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest* request) {
        STRING inputMessage1;
        STRING inputMessage2;
        // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
        if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
            inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
            inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
            digitalWrite((uint8_t)inputMessage1.toInt(), inputMessage2.toInt());
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

    Serial.println("HTTP server started");

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



/* static STRING RelayBoxServer::Processor(const STRING& var)
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
*/


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