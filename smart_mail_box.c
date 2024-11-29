/**
 * @file smart_mail_box.c
 * @brief Smart Mail Notification System using ESP32/ESP8266
 * 
 * This program demonstrates a smart mail notification system that triggers
 * an email alert when a signal (e.g., mail received) is detected. The system
 * uses Wi-Fi to connect to Gmail's SMTP server and send email notifications.
 * It is compatible with both ESP32 and ESP8266 microcontrollers.
 * 
 * @author Muhammad Saeed
 * @date 2024-11-29
 */

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>

// Wi-Fi credentials
#define WIFI_SSID "Your_SSID" /**< Wi-Fi network name */
#define WIFI_PASSWORD "Your_Password" /**< Wi-Fi password */

// GPIO pin configuration
#define SIGNAL_PIN 15 /**< GPIO pin for signal input */
#define ONBOARD_LED 2 /**< GPIO pin for onboard LED */

// SMTP server configuration
#define SMTP_HOST "smtp.gmail.com" /**< SMTP server hostname */
#define SMTP_PORT esp_mail_smtp_port_465 /**< SMTP server port */

// Email credentials
#define AUTHOR_EMAIL "your_email@gmail.com" /**< Sender email address */
#define AUTHOR_PASSWORD "your_password_or_app_password" /**< Sender email password */

// Function prototypes
void smtpCallback(SMTP_Status status);

// Global variables
SMTPSession smtp; /**< SMTP session object */
ESP_Mail_Session session; /**< SMTP session configuration */
SMTP_Message message; /**< Email message object */
int flag = 0; /**< State flag for signal detection */

/**
 * @brief Setup function for initializing the system
 * 
 * Configures Wi-Fi, SMTP session, and GPIO pins. Establishes a connection to
 * the specified Wi-Fi network and sets up the email message configuration.
 */
void setup() {
    Serial.begin(115200);

    pinMode(ONBOARD_LED, OUTPUT);
    pinMode(SIGNAL_PIN, INPUT);

    digitalWrite(ONBOARD_LED, HIGH);
    Serial.println("Connecting to Wi-Fi...");

    // Connect to Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(200);
    }
    Serial.println("\nWi-Fi connected. IP address: ");
    Serial.println(WiFi.localIP());

    // Configure SMTP session
    smtp.debug(1);
    smtp.callback(smtpCallback);

    session.server.host_name = SMTP_HOST;
    session.server.port = SMTP_PORT;
    session.login.email = AUTHOR_EMAIL;
    session.login.password = AUTHOR_PASSWORD;

    // Configure email message
    message.sender.name = "Smart Mailbox";
    message.sender.email = AUTHOR_EMAIL;
    message.subject = "Mail Received Notification";
    message.addRecipient("Recipient", "recipient_email@gmail.com");
    message.text.content = "You have received a mail.";
    message.text.charSet = "us-ascii";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
}

/**
 * @brief Main loop function
 * 
 * Monitors the signal pin and sends an email when the signal is triggered.
 */
void loop() {
    if (digitalRead(SIGNAL_PIN) == LOW && flag == 0) {
        if (!smtp.connect(&session)) return;

        if (!MailClient.sendMail(&smtp, &message)) {
            Serial.println("Error sending email: " + smtp.errorReason());
        } else {
            Serial.println("Email sent successfully.");
        }
        flag = 1;
    } else if (flag == 1 && digitalRead(SIGNAL_PIN) == HIGH) {
        flag = 0;
    }
    delay(2000);
    Serial.print("Flag state: ");
    Serial.println(flag);
}

/**
 * @brief SMTP callback function
 * 
 * Provides status updates for the email sending process.
 * @param status The current SMTP status
 */
void smtpCallback(SMTP_Status status) {
    Serial.println(status.info());

    if (status.success()) {
        Serial.println("Email sent successfully!");
    } else {
        Serial.println("Email sending failed.");
    }
}
