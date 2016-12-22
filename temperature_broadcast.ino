#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define BUFFER_SIZE 128

// Initialize Wi-Fi information; SSID and passphrase
const char* SSID = "SSID_OF_THE_WIFI_NETWORK";
const char* passphrase = "PASSPHRASE_OF_THE_WIFI_NETWORK";
// Set the broadcast port for UDP messages
const unsigned int broadcast_port = 12345;
// Initialize broadcast IP address
IPAddress broadcast_ip;
// Initialize a string for saving the MAC address of the device
String mac_address;
// Initialize UDP library
WiFiUDP udp;
// Initialize DHT-11 on pin D4
DHT dht(D4, DHT11);

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

    // Create wifi broadcast address from subnet mask and the gateway IP address
    //
    // With subnet mask 255.255.0.0 and gateway IP 10.0.0.1 this becomes 10.0.255.255
    //
    // https://github.com/esp8266/Arduino/issues/1252#issuecomment-174159835
    broadcast_ip = ~WiFi.subnetMask() | WiFi.gatewayIP();
    // Set MAC address, used to identify the sending device
    mac_address = WiFi.macAddress();

    // Print wifi information to serial port
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.print("MAC address: ");
    Serial.println(mac_address);
    Serial.print("Broadcast IP address: ");
    Serial.println(broadcast_ip);

    // setup DHT
    dht.begin();
}

void loop() {
    // Delay for 2000 milliseconds -> 2 seconds
    delay(2000);

    // Create JSON message
    StaticJsonBuffer<BUFFER_SIZE> jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    // Read temperature to the JSON object
    json["temperature"] = dht.readTemperature();
    // Read humidity
    json["humidity"] = dht.readHumidity();
    // Set sender to the MAC address of the device
    json["sender"] = mac_address;

    // Initialize the UDP packet, send to broadcast_ip and broadcast_port
    udp.beginPacket(broadcast_ip, broadcast_port);

    // Create a character array to hold JSON message
    char json_message[BUFFER_SIZE];
    // "Print" JSON to the character array
    json.printTo(json_message, sizeof(json_message));
    // Set packet content
    udp.write(json_message);
    // End packet, sending it
    udp.endPacket();
}
