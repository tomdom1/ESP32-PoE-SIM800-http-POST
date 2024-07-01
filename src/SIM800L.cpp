#include "SIM800L.h"

const char SIM_PIN[] = "6993";
HardwareSerial sim800l(2);
bool isConnected = false;

std::vector<String> receivedSMS; // Zmienna globalna do przechowywania odebranych SMS-ów


void sim800lSetup() {
    sim800l.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
    sendATCommand("AT", 2000);
    sendATCommand("AT+CPIN?", 2000);
    sendATCommand(String("AT+CPIN=") + SIM_PIN, 2000);
    configureBand();
    resetAndConfigureModem();
    // setupGPRS();
    checkNetworkConnection();
}

String sendATCommand(String command, int timeout) {
    sim800l.println(command);
    long int time = millis();
    String response = "";

    while ((millis() - time) < timeout) {
        while (sim800l.available()) {
            char c = sim800l.read();
            response += c;
        }
    }
    Serial.println("Odpowiedź na komendę " + command + ": " + response);
    return response;
}

bool isRegistered(String response) {
    if (response.indexOf("+CREG: 0,1") >= 0 || response.indexOf("+CREG: 0,5") >= 0) {
        return true;
    }
    return false;
}

// Check network z uzyciem isRegistered 
void checkNetworkConnection() {
    String response = sendATCommand("AT+CREG?", 5000);
    delay(3000);

    Serial.println("Odpowiedź CREG: " + response);

    if (isRegistered(response)) {
        Serial.println("Zarejestrowano w sieci.");
        isConnected = true;
    } else {
        Serial.println("Brak rejestracji w sieci. Wybieranie operatora...");
        selectOperator();
        checkNetworkConnection();
    }
}


void checkSignalStrength() {
    sendATCommand("AT+CSQ", 2000);
}

void checkSIMStatus() {
    sendATCommand("AT+CPIN?", 2000);
}

void restartModem() {
    sendATCommand("AT+CFUN=1,1", 5000);
    delay(10000);
}

void resetAndConfigureModem() {
    sendATCommand("AT+CFUN=1,1", 10000);
    delay(10000);
    sendATCommand("AT+CNMP=2", 2000);
    sendATCommand("AT+CMNB=1", 2000);
}

void selectOperator() {
    sendATCommand("AT+COPS=?", 2000);
    sendATCommand("AT+COPS=1,2,\"26003\"", 2000);
    delay(10000);
}

void configureBand() {
    sendATCommand("AT+CBAND?", 2000);
    sendATCommand("AT+CBAND=\"ALL_BAND\"", 2000);
}

// void setupGPRS() {
//     sendATCommand("AT+CGATT=1", 10000);
//     configureAPN();
// }

// void configureAPN() {
//     sendATCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"", 5000);
//     sendATCommand("AT+SAPBR=3,1,\"APN\",\"internet\"", 5000);
//     sendATCommand("AT+SAPBR=1,1", 5000);
//     sendATCommand("AT+SAPBR=2,1", 5000);
// }

// void sendToZabbix(String url) {
//     sendATCommand("AT+HTTPINIT", 5000);
//     sendATCommand("AT+HTTPPARA=\"CID\",1", 5000);
//     sendATCommand("AT+HTTPPARA=\"URL\",\"" + url + "\"", 5000);
//     sendATCommand("AT+HTTPACTION=0", 10000);
//     sendATCommand("AT+HTTPTERM", 5000);
// }


void checkSMS() {
    sendATCommand("AT+CMGF=1", 2000);
    sendATCommand("AT+CPMS=\"SM\",\"SM\",\"SM\"", 2000);
    String response = sendATCommand("AT+CMGL=\"REC UNREAD\"", 5000);

    // Logowanie odpowiedzi
    Serial.println("Odpowiedź AT+CMGL: " + response);

    if (response.indexOf("+CMGL") >= 0) {
        // Przechowywanie odebranych SMS-ów
        receivedSMS.push_back(response);
    } else {
        Serial.println("Brak nowych SMS-ów.");
    }

    // Przykładowa analiza odebranych SMS
    while (sim800l.available()) {
        String smsContent = "";
        while (sim800l.available()) {
            char c = sim800l.read();
            smsContent += c;
        }
        
        String senderNumber;
        parseSenderNumber(smsContent, senderNumber);
    
    }
}


void parseSenderNumber(String &smsContent, String &senderNumber) {
    int index = smsContent.indexOf("+CMGR:");
    if (index >= 0) {
        int start = smsContent.indexOf("\"", index + 1) + 1;
        int end = smsContent.indexOf("\"", start);
        senderNumber = smsContent.substring(start, end);
    }
}


bool sendSMS(String number, String message) {
    sendATCommand("AT+CMGF=1", 2000);
    sendATCommand("AT+CMGS=\"" + number + "\"", 2000);
    sim800l.print(message);
    sim800l.write(26);

    long int time = millis();
    String response = "";
    while ((millis() - time) < 10000) {
        while (sim800l.available()) {
            char c = sim800l.read();
            response += c;
        }
    }
    Serial.println("Odpowiedź: " + response);

    if (response.indexOf("OK") != -1) {
        return true;
    } else {
        return false;
    }
}

void monitorConnection() {
    checkNetworkConnection();
    checkSignalStrength();
    checkSIMStatus();
    
    // if (!isConnected) {
    //     setupGPRS();
    // }
}
