#include "HTTPServer.h"
#include "SIM800L.h"

WebServer server(80);

void handleSendSMS() {
    if (server.hasArg("number") && server.hasArg("message")) {
        String number = server.arg("number");
        String message = server.arg("message");
        bool status = sendSMS(number, message);
        if (status) {
            server.send(200, "application/json", "{\"statusSend\": true}");
        } else {
            server.send(200, "application/json", "{\"statusSend\": false}");
        }
    } else {
        server.send(400, "application/json", "{\"error\": \"Missing number or message argument\"}");
    }
}

void handleCheckSMS() {
    String response = "List of received SMS:\n";
    for (const auto& sms : receivedSMS) {
        response += sms + "\n";
    }
    server.send(200, "text/plain", response);
}

void setupServer() {
    server.on("/sendSMS", HTTP_POST, handleSendSMS);
    server.on("/checkSMS", HTTP_GET, handleCheckSMS);
    server.begin();
    Serial.println("HTTP server started");
}
