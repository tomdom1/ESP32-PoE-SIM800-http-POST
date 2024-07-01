#ifndef SIM800L_H
#define SIM800L_H

#include <HardwareSerial.h>
#include <vector>


extern const char SIM_PIN[];
extern HardwareSerial sim800l;
extern bool isConnected;

extern std::vector<String> receivedSMS;

#define RX_PIN 16
#define TX_PIN 4

void sim800lSetup();
String sendATCommand(String command, int timeout);
bool isRegistered(String response);
void checkNetworkConnection();
void checkSignalStrength();
void checkSIMStatus();
void restartModem();
void configureNetworkMode();
void resetAndConfigureModem();
void selectOperator();
void configureBand();
// void setupGPRS();
// void configureAPN();
void sendToZabbix(String url);
void checkSMS();
// void processSMS(String smsContent, String senderNumber);
bool sendSMS(String number, String message);
void monitorConnection();
void parseSenderNumber(String &smsContent, String &senderNumber);

#endif
