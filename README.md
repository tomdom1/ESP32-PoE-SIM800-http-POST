# Project: Sending SMS using ESP32-PoE and SIM800L

## Project Description

This demonstration project shows how to integrate ESP32-PoE with the SIM800L module to send and receive SMS. The project utilizes TX/RX communication between the modules and allows sending SMS via HTTP POST. It connects to both ETH and WIFI networks.


## Hardware Requirements

- ESP32-PoE 
[Project Page](https://www.olimex.com/Products/IoT/ESP32/ESP32-POE/open-source-hardware)
- GSM Module SIM800L
- Active SIM card 
- 4V Power supply
- Connection wires

## Software Requirements

- PlatformIO installed in Visual Studio Code

## Hardware Connection

1. **Connecting the SIM800L module to ESP32-PoE:**
   - **SIM800L TX** to **ESP32 RX (GPIO16)**
   - **SIM800L RX** to **ESP32 TX (GPIO4)**
    - **Power**: Ensure the SIM800L module is powered with the appropriate voltage (3.7V - 4.2V).

## Project Configuration

### Step 1: Cloning the Repository
````
git clone https://github.com/tomdom1/ESP32-PoE-SIM800-http-POST.git

cd ESP32-PoE-SIM800-http-POST
````

### Step 2: Initializing PlatformIO
Ensure that PlatformIO is installed in Visual Studio Code. Open the project folder in Visual Studio Code.

#### Step 3: Project Configuration
Configure the project files, including platformio.ini, to ensure you have the correct settings for ESP32-PoE and SIM800L.

#### Step 4: Uploading the Code 
PConnect the ESP32-PoE to your computer and upload the code using PlatformIO:

````
platformio run --target upload
````

### Usage

To send an SMS, make an HTTP POST request to the /sendSMS endpoint with the number and message parameters.

Example request:

````javascript 
POST /sendSMS HTTP/1.1
Host: <IP_ESP32>
Content-Type: application/json

{
    "number": "+48123456789",
    "message": "Testowa wiadomość"
}
````

### Checking Received SMS
To check received SMS messages, make an HTTP GET request to the /checkSMS endpoint.

Example request:

````js
GET /checkSMS HTTP/1.1
Host: <IP_ESP32>
````

## Project Files
- main.cpp - main project file.
- SIM800L.h i SIM800L.cpp - files for handling the SIM800L module.
- Network.h i Network.cpp - files for handling network connections (Ethernet/WiFi).
- HTTPServer.h i HTTPServer.cpp - files for handling the HTTP server.

### License
This project is licensed under the terms of the MIT license. See the [LICENSE](https://github.com/tomdom1/ESP32-PoE-SIM800-http-POST/blob/main/LICENSE) file for more information.

If you have any questions or need assistance, open an issue in the GitHub repository or contact me directly.

This README file contains all essential information about the project, including description, requirements, configuration steps, usage instructions, and license information. You can customize it to your specific needs or add additional sections as you see fit.




