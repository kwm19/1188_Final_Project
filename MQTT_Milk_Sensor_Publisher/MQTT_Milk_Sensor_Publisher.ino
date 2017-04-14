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

#define       WIFI_SSID         "rambo"
#define       WIFI_PWD          "ferrari1"
//#define       WIFI_SSID         "FBI Van 3"
//#define       WIFI_PWD          "brightquail370"

PubSubClient client(server, 1883, callback, wclient);

char inputButtonState;

int sensorPin1 = A0;    // P5.5,  select the input pin for the Milk
int ledPin1 = GREEN_LED;      // select the pin for the GREEN LED (P2.1)
int sensorValue1 = 0;  // variable to store the value coming from the sensor

int sensorPin2 = A1;    // P5.4,  select the input pin for the Eggs
int ledPin2 = BLUE_LED;      // select the pin for the BLUE LED (P2.2)
int sensorValue2 = 0;  // variable to store the value coming from the sensor

char message_buff[100];


void callback(char* inTopic, byte* payload, unsigned int length){
// Handle callback here

//  int i = 0;
//
//  Serial.println("Message arrived:  topic: " + String(inTopic));
//  Serial.println("Length: " + String(length,DEC));
//  
//  // create character buffer with ending null terminator (string)
//  for(i=0; i<length; i++) {
//    message_buff[i] = payload[i];
//  }
//  message_buff[i] = '\0';
//  
//  String msgString = String(message_buff);
//  
//  Serial.println("Payload: " + msgString);
//  
//  if (msgString.equals("{1}")) {
//    digitalWrite(ledPin1, HIGH);  
//  } else {
//    digitalWrite(ledPin1, LOW);  
//  }

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

  pinMode(ledPin1, OUTPUT);  
  pinMode(ledPin2, OUTPUT); 

}

void loop()
{
  // read the value from the sensor:
  sensorValue1 = analogRead(sensorPin1);   

  sensorValue2 = analogRead(sensorPin2) ;

  // convert into to char array
  String stringBuild = String(sensorValue1)  + "," + String(sensorValue2);
  int str_len = stringBuild.length() + 1;  // Length (with one extra character for the null terminator)
  char char_array[str_len];  // Prepare the character array (the buffer) 
  stringBuild.toCharArray(char_array, str_len);  // Copy it over 

  
  // publish data to MQTT broker
  if (client.connect("LaunchPadClient")) {
    client.publish("outTopicKMonto", char_array);
//    client.subscribe("inTopicKMonto");
    Serial.println("Publishing successful!");
    client.disconnect();
  }
  //every 15 seconds
  delay(15000);

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


