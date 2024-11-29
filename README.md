# Smart Mail Notification System

## Overview
The **Smart Mail Notification System** is an IoT project designed to notify users via email whenever a physical signal (e.g., mail received) is detected. The system uses an ESP32/ESP8266 microcontroller and Gmail's SMTP server to deliver email alerts in real-time.

---

## Features
- **Automated Notifications**: Sends email alerts when triggered.
- **Wi-Fi Connectivity**: Establishes a reliable connection to a local network.
- **Real-Time Monitoring**: Continuously monitors the sensor state.
- **Cross-Platform Compatibility**: Supports ESP32 and ESP8266 boards.

---

## Dependencies
- **ESP Mail Client Library**: [Documentation](https://github.com/mobizt/ESP-Mail-Client)
- **Arduino Core for ESP32/ESP8266**

---

## Hardware Requirements
- **Microcontroller**: ESP32/ESP8266
- **Sensor**: Any digital signal input device (e.g., mail detection sensor).
- **Connections**:
  - `GPIO15` for signal input
  - `GPIO2` for onboard LED (status indicator)

---

## Setup Instructions

### Hardware Setup
1. Connect the signal input device to GPIO15.
2. Use GPIO2 for an onboard LED.

### Software Setup
1. Install Arduino IDE.
2. Install the required libraries:
   - Go to **Tools** > **Manage Libraries**.
   - Search and install **ESP Mail Client**.
3. Update the credentials in the code:
   ```c
   #define WIFI_SSID "Your_SSID"
   #define WIFI_PASSWORD "Your_Password"
   #define AUTHOR_EMAIL "your_email@gmail.com"
   #define AUTHOR_PASSWORD "your_password_or_app_password"
## Acknowledgments
This project is based on the ESP Mail Client library and utilizes open-source tools like Arduino IDE for development.