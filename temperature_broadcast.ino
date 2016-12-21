#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Initialize Wi-Fi information; SSID and passphrase
const char* SSID = "SSID_OF_THE_WIFI_NETWORK";
const char* passphrase = "PASSPHRASE_OF_THE_WIFI_NETWORK";
// Set the broadcast port for UDP messages
const unsigned int broadcast_port = 12345;
// Initialize broadcast IP address
IPAddress broadcast_ip;
// Initialize UDP library
WiFiUDP udp;

void setup() {
    // Initialize serial port with baudrate of 115200
    Serial.begin(115200);
    // Wait for serial port to be ready
    while (!Serial) {}

    // Begin connecting to the wifi
    WiFi.begin(SSID, passphrase);
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        // Display "progress bar"
        Serial.print(".");
    }

    // Create wifi broadcast address subnet mask with the gateway IP address
    //
    // With subnet mask 255.255.0.0 and gateway IP 10.0.0.1
    // this becomes 10.0.255.255
    //
    // https://github.com/esp8266/Arduino/issues/1252#issuecomment-174159835
    broadcast_ip = ~WiFi.subnetMask() | WiFi.gatewayIP();

    // Print wifi information to serial port
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("Broadcast IP address: ");
    Serial.println(broadcast_ip);
}

void loop() {
    // Delay for 2000 milliseconds -> 2 seconds
    delay(2000);
    // Initialize the UDP packet, send to broadcast_ip and broadcast_port
    udp.beginPacket(broadcast_ip, broadcast_port);
    // Set packet content
    udp.write("Hello from ESP2866 at %s!");
    // End packet, sending it
    udp.endPacket();
}
