#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>


// Stores ssid and password 
#include "secrets.h"

AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.setHostname("ESP32_1");
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Welcome to the ESP32 Async REST API");
  });

   server.on("/post-json", HTTP_POST, [](AsyncWebServerRequest *request) {}, NULL, [](AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) 
   {
    // Check if the total size of the expected data is greater than zero
    if (total > 0) {
      DynamicJsonDocument doc(1024);
      DeserializationError error = deserializeJson(doc, data);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        request->send(400, "text/plain", "Bad Request: JSON parsing failed");
        return;
      }

      int intValue = doc["intValue"]; // Extract integer value
      const char* stringValue = doc["stringValue"]; // Extract string value

      String message = "Received int: " + String(intValue) + ", string: " + stringValue;
      request->send(200, "text/plain", message);
    } else {
      request->send(400, "text/plain", "Bad Request: No JSON found");
    }
  });

  server.onNotFound(notFound);

  server.begin();
}


void loop() {
  // No need to call handleClient in the loop for the AsyncWebServer
}
