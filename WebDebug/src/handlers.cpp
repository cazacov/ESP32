#include "handlers.h"
#include "base64.h"

AsyncCallbackJsonWebHandler* postDataHandler = new AsyncCallbackJsonWebHandler("/data",
     [](AsyncWebServerRequest *request, 
     JsonVariant &json) {
  StaticJsonDocument<500> jsonDoc;
  if (json.is<JsonArray>())
  {
    jsonDoc = json.as<JsonArray>();
  }
  else if (json.is<JsonObject>())
  {
    jsonDoc = json.as<JsonObject>();
  }
  const char* data64 = jsonDoc["base64"];

  if (data64) {
    Serial.print("Got base64 data: ");
    Serial.println(data64);
    Serial.print("Base64 length: ");
    Serial.println(strlen(data64));
    std::vector<uint8_t> binArray = base64decode(data64);
    Serial.print("Binary length: ");
    Serial.println(binArray.size());
    request->send(200, "application/json", "{ \"accepted\": true }");
  }

  const char*  german = jsonDoc["german"];
  if (german) {
    Serial.print("German text length in bytes: ");
    Serial.println(strlen(german));
  }

  else {
    request->send(400, "application/json", "{ \"error\": \"Invalid request\" }");
  }
});

void notFoundHandler(AsyncWebServerRequest* request) {
    if (request->method() == HTTP_OPTIONS) {
      request->send(200);
    } else {
      request->send(404);
    }
};