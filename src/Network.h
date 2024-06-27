#ifndef NETWORK_H
#define NETWORK_H

#include <ETH.h>
#include <WiFi.h>

void WiFiEvent(WiFiEvent_t event);
void setupEthernet();
void setupWiFi();

#endif
