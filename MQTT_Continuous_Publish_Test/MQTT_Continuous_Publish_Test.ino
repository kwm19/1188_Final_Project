/*
Continuously publish analog sensor readings from pin24.
This example reads analog pin 24, converts the int into a char array and publishes it over MQTT. 
  - read analog input on pin 24
  - typecase sensor reading to a character array
  - connects to an MQTT broker
  - publishes sensor reading to the topic "outTopic"
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h> //only required if using an MCU LaunchPad + CC3100 BoosterPack. Not needed for CC3200 LaunchPad
WiFiClient wclient;

byte server[] = { 198, 41, 30, 241 }; //  Public MQTT Brokers: http://mqtt.org/wiki/doku.php/public_brokers
byte ip[]     = { 172, 16, 0, 100 };

char sensorRead[4];

#define       WIFI_SSID         "FBI Van 3"
#define       WIFI_PWD          "brightquail370"

PubSubClient client(server, 1883, callback, wclient);

char inputButtonState;

void callback(char* inTopic, byte* payload, unsigned int length){
// Handle callback here
}

void setup()
{
  //Initialize serial and wait for port to open:
  Serial.begin(115200);

  Serial.println("Start WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PWD);
  while(WiFi.localIP() == INADDR_NONE) {
    Serial.print(".");
    delay(300);
  }
  Serial.println("");

  printWifiStatus();

  pinMode(78, OUTPUT);        // Initialize Arduino Digital Pins 8 as output for connecting LED
  pinMode(73,INPUT);         // Initialize Arduino Digital Pins 12 as input for connecting Pushbutton

}

void loop()
{
  // read the input on analog pin:
  String buttonValue;
  inputButtonState = digitalRead(73); //Read the Pushbutton state.
  if (inputButtonState == HIGH) 
  {     
    digitalWrite(78, HIGH);  //Switch on LED
    buttonValue = "Button Pushed";
  } 
  else 
  {
    digitalWrite(78, LOW);   //Switch off LED
    buttonValue = "Button NOT Pushed";
  }

  // convert into to char array
  String str = (String)buttonValue; 
  int str_len = str.length() + 1;  // Length (with one extra character for the null terminator)
  char char_array[str_len];  // Prepare the character array (the buffer) 
  str.toCharArray(char_array, str_len);  // Copy it over 
  
  // publish data to MQTT broker
  if (client.connect("LaunchPadClient")) {
    client.publish("outTopicKMonto", char_array);
    //client.subscribe("inTopic");
    Serial.println("Publishing successful!");
    client.disconnect();
  }

  delay(5000);

}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


