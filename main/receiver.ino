/*
  Connect to WIFI and wait for serial input, If serial input recived, post data to server.
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Artha Penn";
const char* password = "s123456789";
String value="0";

//Your Domain name with URL path or IP address with path
const char* serverName = "http://bhupali.000webhostapp.com";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if(Serial.available()>0)    //Checks is there any data in buffer 
          {
            //char value = Serial.read();
            value =Serial.readString();
            Serial.print("Reading:");
            Serial.print(value);  //Read serial data byte and send back to serial monitor
                //Check WiFi connection status
            if(WiFi.status()== WL_CONNECTED){
              WiFiClient client;
              HTTPClient http;
              
              // Your Domain name with URL path or IP address with path
              http.begin(client, serverName);          
              // Specify content-type header
              http.addHeader("Content-Type", "application/x-www-form-urlencoded");
              // Data to send with HTTP POST
              String httpRequestData = "api_key=tPmAT5Ab3j7F9&level=" + value;       
              // Send HTTP POST request
              int httpResponseCode = http.POST(httpRequestData);
                   
              Serial.print("HTTP Response code: ");
              Serial.println(httpResponseCode);
                              
              // Free resources
              http.end();
              digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
              delay(50);                      // Wait for a second
              digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
              delay(950);  
  
            }
            else {
              Serial.println("WiFi Disconnected");
            }
          }
}
