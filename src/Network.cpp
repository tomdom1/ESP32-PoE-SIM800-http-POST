#include "Network.h"

const char* ssid = "your_ssid_wifi";
const char* password = "your_pass_wifi";

void WiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case SYSTEM_EVENT_ETH_CONNECTED:
            Serial.println("ETH Connected");
            break;
        case SYSTEM_EVENT_ETH_DISCONNECTED:
            Serial.println("ETH Disconnected");
            break;
        case SYSTEM_EVENT_ETH_START:
            Serial.println("ETH Started");
            ETH.setHostname("esp32-ethernet");
            break;
        case SYSTEM_EVENT_ETH_GOT_IP:
            Serial.print("ETH IP: ");
            Serial.println(ETH.localIP());
            break;
        case SYSTEM_EVENT_ETH_STOP:
            Serial.println("ETH Stopped");
            break;
        default:
            break;
    }
}

void setupEthernet() {
    WiFi.onEvent(WiFiEvent);
    ETH.begin();
}

void setupWiFi() {
    Serial.println("Connecting to Wi-Fi...");
    WiFi.begin(ssid, password);

    int maxAttempts = 20;
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED && attempt < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempt++;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.print("WiFi connected. IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Failed to connect to Wi-Fi");
    }
}
