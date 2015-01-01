/*
  Basic Pactola API Client
 
  This sketch connects to Pactola.io and sends a notification.
  It is heavily inspired by the Ethernet web client demo.
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
  created December 31, 2014
  by Thaddeus Ternes
  www.bluetoo.co

 */

#include <SPI.h>
#include <Ethernet.h>

// ------------------------------------------
// Pactola Device ID
// ------------------------------------------
String device = "deviceIdHere";

// ------------------------------------------
// Pactola Notification (JSON)
// ------------------------------------------
String json = "{ \"title\" : \"Arduino Test\", \"message\" : \"It Works :)\" }";

// ------------------------------------------
// Pactola Server
// ------------------------------------------
char server[] = "pactola.io";

// ------------------------------------------
// Ethernet configuration
// ------------------------------------------

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };

// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10,0,1,235);

// ------------------------------------------
// Sketch
// ------------------------------------------

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    
    Serial.println("connected");

    // POST the notification (see http://pactola.io/api for details)
    client.println(String("POST /"+device+"/notification HTTP/1.1"));
    client.println("Host: " + String(server));
    client.println(String("Content-Length: " + String(json.length())));
    client.println("Connection: close");
    client.println();
    client.println(json);
  } 
  else {
    // connection to server failed
    Serial.println("connection failed");
  }
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // all finished..
    while(true);
  }
}

