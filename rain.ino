#include <SPI.h>
#include <WiFi.h>

char ssid[] = "XXXXXXX";
char password[] = "XXXXXX";

int status = WL_IDLE_STATUS;

WiFiClient rainClient;

char server[] = "api.thingspeak.com";
String writeAPIKey = "XXXXXXXXXX";

int pin_d = 7; // Digital pin connected to D0
int pin_a = A5; // Analog pin connected to A0
int val_d = 0; // Stores digital value
int val_a = 0; // Stores analog value

void setup()
{
  pinMode(pin_d, INPUT);
  pinMode(pin_a, INPUT);
  /**
     Sets the data rate in bits per second (baud) for serial data transmission.
     For communicating with the computer, use one of these rates: 300, 600, 1200, 2400, 4800, 9600, 14400, 19200, 28800, 38400, 57600, or 115200.
     You can, however, specify other rates - for example, to communicate over pins 0 and 1 with a component that requires a particular baud rate.
  */
  Serial.begin(9600);

   check for the presence of the shield:
    while (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      delay(3000);
    }

  scanNetworks();

  // attempt to connect to Wifi network
  while (WiFi.status() != WL_CONNECTED) {
    // Connect to WPA/WPA2 Wi-Fi network
    status = WiFi.begin(ssid, password);
    if (status != WL_CONNECTED) {
      Serial.print("Status: ");
      Serial.println(status);
      Serial.println("Will try to connect again in 10 seconds...");
      delay(10000);
    }
  }
}

void scanNetworks() {
  // scan for nearby networks:
  Serial.println("** Scan Networks **");
  byte numSsid = WiFi.scanNetworks();

  // print the list of networks seen:
  Serial.print("SSID List:");
  Serial.println(numSsid);
  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    Serial.print(thisNet);
    Serial.print(") Network: ");
    Serial.println(WiFi.SSID(thisNet));
  }
}

// Posts data to thingspeak cloud
void postData(int value, String message) {

  // create data string to send to ThingSpeak
  String data = String(message + String(value, DEC));

  // POST data to ThingSpeak
  if (rainClient.connect(server, 80)) {
    rainClient.println("POST /update HTTP/1.1");
    rainClient.println("Host: api.thingspeak.com");
    rainClient.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
    rainClient.print("Content-Length: ");
    rainClient.print(data.length());
    rainClient.print("\n\n");
    rainClient.print(data);
    // close any connection before sending a new request
    rainClient.stop();
  }
}

void loop()
{
  val_d = digitalRead(pin_d);
  val_a = analogRead(pin_a);
  String message;

  Serial.print("Digital value: ");
  Serial.println(val_d);
  Serial.print("Analog value : ");
  Serial.println(val_a);


  // Digital output
  if (val_d == 1)
  {
    message = "Raining! =D";
    Serial.println(message);
  }
  else
  {
    message = "Not raining... =(";
    Serial.println(message);
  }
  postData(val_d, message);

  // Analog output
  if (val_a > 700)
  {
    message = "RUN TO THE HILLS!";
    Serial.println(message);
  }
  else if (val_a > 500 && val_a < 700)
  {
    message = "Wow! We have a storm here!";
    Serial.println(message);
  }
  else if (val_a > 300 && val_a < 500)
  {
    message = "Yay! RAIN!";
    Serial.println(message);
  }
  else if (val_a > 100 && val_a < 300)
  {
    message = "Kind normal...";
    Serial.println(message);
  }
  else if (val_a < 100)
  {
    message = "Are we in Atacama desert?";
    Serial.println(message);
  }
  postData(val_a, message);
  delay(5000);
}
