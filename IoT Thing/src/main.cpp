#include "WiFi.h"
#include "PubSubClient.h"
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include <mqtt_client.h>


char* ssid = "K8";
char* password =  "dogsminusone";

const char* default_ssid = "Apperature Science";
const char* default_password = "gladossux";
 
EthernetClient ethClient;
PubSubClient client(ethClient);
 
const char* mqtt_server = "192.168.1.5";

void setup(){
  
  pinMode(BUILTIN_LED, OUTPUT);
  client.setServer(mqtt_server, 1883);
  Serial.begin(115200); 

  PubSubClient(client);
  
  while (WiFi.status() != WL_CONNECTED) {
    for(int i = 0; i< 10 && WiFi.status() != WL_CONNECTED; i++)
    {
    delay(500);
    Serial.println("Connecting to WiFi..");
    WiFi.begin(ssid, password);
    }

    for(int i = 0; i<10 && WiFi.status() != WL_CONNECTED; i++)
    {
    delay(500);
    Serial.println("Could not connect searching for default...");
    //WiFi.begin(default_ssid, default_password);
    }
  }
 if(WiFi.status() == WL_CONNECTED)
    {
      digitalWrite(BUILTIN_LED, HIGH);
      Serial.println("Connected to the WiFi network");
      Serial.println("Ip: ");
      Serial.println(WiFi.localIP());
    }
}

void mqttconnect() {
  // Loop until reconnected
  while (!client.connected()) {
    Serial.print("MQTT connecting ...");
    // client ID 
    String clientId = "ESP32Client";
    // connect now 
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // subscribe topic with default QoS 0
      client.subscribe("Test");
    } else {
      Serial.print("failed, status code =");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void callback(char* topic, byte *payload, unsigned int length) {
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:"); 
    Serial.write(payload, length);
    Serial.println();
}


/*
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())){
      Serial.println("connected");
      //Once connected, publish an announcement...
      client.publish("Test", "hello world");
      // ... and resubscribe
      client.subscribe("Test");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
}
}
*/
void loop(){

  Serial.println("Ur mom gay");

  delay(1000);
  if (!client.connected()) {
    mqttconnect();
  }
  client.publish("Test", "Ur mom gay");
}
