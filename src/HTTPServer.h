#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <WebServer.h>

extern WebServer server;

void handleSendSMS();
void handleCheckSMS();
void setupServer();

#endif
