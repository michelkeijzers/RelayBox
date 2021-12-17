#include "HtmlComposer.h"

#include "RelayBox.h"
#include "NtpServerTime.h" //TODO

class RelayBox;

HtmlComposer::HtmlComposer(RelayBox* relayBox)
: _relayBox(*relayBox)
{
}


void HtmlComposer::Compose(STRING& ptr)
{
    ptr = R"(
        <!DOCTYPE html> <html>
        <head>
            <meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
            <meta http-equiv=refresh content="1">
            <link rel="icon" href="data:,">

            <style>
                html {
                    font-family: Arial, Helvetica, sans-serif;
                    text-align: center;
                }
    
                h1 {
                    font-size: 1.8rem;
                    color: white;
                }
    
                h2{
                    font-size: 1.5rem;
                    font-weight: bold;
                    color: #143642;
                }

                .topnav {
                    overflow: hidden;
                    background-color: #143642;
                }

                body {
                    margin: 0;
                }
    
                .content {
                    padding: 30px;
                    max-width: 600px;
                    margin: 0 auto;
                }

                .card {
                    background-color: #F8F7F9;;
                    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
                    padding-top:10px;
                    padding-bottom:20px;
                }

                .button {
                    padding: 15px 50px;
                    font-size: 24px;
                    text-align: center;
                    outline: none;
                    color: #fff;
                    background-color: #0f8b8d;
                    border: none;
                    border-radius: 5px;
                    -webkit-touch-callout: none;
                    -webkit-user-select: none;
                    -khtml-user-select: none;
                    -moz-user-select: none;
                    -ms-user-select: none;
                    user-select: none;
                    -webkit-tap-highlight-color: rgba(0,0,0,0);
                }

                /*.button:hover {background-color: #0f8b8d}*/
                    .button:active {
                    background-color: #0f8b8d;
                    box-shadow: 2 2px #CDCDCD;
                    transform: translateY(2px);
                }

                .state {
                    font-size: 1.5rem;
                    color:#8c8c8c;
                    font-weight: bold;
                }
            </style>

            <title>LED Control</title>
        </head>

        <body>
            <div class="topnav">
                <h1>ESP32 Relay Box 0.1</h1>
            </div>

            <div class="content">
                <div class="card">
                    <h2>Output - Button 1</h2>
                    <p class="state">state: <span id="state">%STATE%</span></p>
                    <p><button id="button" class="button">Toggle</button</p>
                </div>
            </div>

            <script>
                var gateway = `ws://${window.location.hostname}/ws`;
                var websocket;
    
                window.addEventListener('load', onLoad);
        
                function initWebSocket() {
                    console.log('Trying to open a WebSocket connection...');
                    websocket = new WebSocket(gateway);
                    websocket.onopen    = onOpen;
                    websocket.onclose   = onClose;
                    websocket.onmessage = onMessage; // <-- add this line
                }

                function onOpen(event) {
                    console.log('Connection opened');
                }
          
                function onClose(event) {
                    console.log('Connection closed');
                    setTimeout(initWebSocket, 2000);
                }
        
                function onMessage(event) {
                    var state;
                    if (event.data == "1"){
                      state = "ON";
                    }
                    else{
                      state = "OFF";
                    }
                    document.getElementById('state').innerHTML = state;
                }
        
                function onLoad(event) {
                    initWebSocket();
                    initButton();
                }
       
                function initButton() {
                    document.getElementById('button').addEventListener('click', toggle);
                }
        
                function toggle(){
                    websocket.send('toggle');
                }

            </script>
        </body>
        </html>
    )";

    /*
    if (_relayBox.GetFourChannelRelayModule().GetRelayState(0))
    {
        ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
    }
    else
    {
        ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
    }

    if (_relayBox.GetFourChannelRelayModule().GetRelayState(1))
    {
        ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
    }
    else
    {
        ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";
    }

    char buffer[256];

    ptr += "<p>LDR value: ";
    sprintf_s(buffer, "%d", _relayBox.GetLdr().GetLdrValue());
    ptr += buffer;
    ptr += "</p>";

    ptr += "<p>Current Date/Time: ";
    sprintf_s(buffer, "%s", _relayBox.GetTime().TimeAsString());
    ptr += buffer;
    ptr += "</p>";

    ptr += "<p>Temperature: ";
    sprintf_s(buffer, "%.1f", _relayBox.GetTempSensor().getTempCByIndex(0));
    ptr += buffer;
    ptr += "</p>";

    ptr += "<p>PIR Motion Sensor: ";
    if (_relayBox.GetPirMotionSensor().SecondsUntilInitialized() == 0)
    {
        if (_relayBox.GetPirMotionSensor().IsMotionDetected())
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
        sprintf_s(buffer, "Initializing for %d s", _relayBox.GetPirMotionSensor().SecondsUntilInitialized());
        ptr += buffer;
    }

    ptr += "</p>";

    ptr += "</body>\n";
    ptr += "</html>\n";
    )";
*/
};
