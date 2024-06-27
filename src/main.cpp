#include <Arduino.h>
#include "Network.h"
#include "HTTPServer.h"
#include "SIM800L.h"

void setup() {
    Serial.begin(115200);
    sim800lSetup();

    setupEthernet();
    delay(3000);

    if (!ETH.linkUp()) {
        setupWiFi();
    }

    setupServer();
}

void loop() {
    server.handleClient();
    monitorConnection();
    delay(10000);
}
