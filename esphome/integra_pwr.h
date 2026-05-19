#include "esphome.h"
#include <ESP8266WiFi.h>

class IntegraPwrListener : public Component {
 public:
  WiFiClient client;
  const char* integra_ip = "10.0.168.212"; 
  const uint16_t port = 60128;

  void setup() override {
    ESP_LOGI("integra", "Targeting DHC 60.7 at %s", integra_ip);
  }

  void loop() override {
    if (!client.connected()) {
      static uint32_t last_reconnect = 0;
      if (millis() - last_reconnect > 10000) { // Retry every 10s
        last_reconnect = millis();
        if (client.connect(integra_ip, port)) {
          ESP_LOGI("integra", "eISCP Connection Established!");
        }
      }
      return;
    }

    if (client.available()) {
      String msg = client.readStringUntil('\n');
      
      // ISCP Power State Logic
      if (msg.indexOf("!1PWR01") != -1) {
        id(amp_relay).turn_on();
        ESP_LOGD("integra", "ISCP MATCH: Main Power ON");
      } 
      else if (msg.indexOf("!1PWR00") != -1) {
        id(amp_relay).turn_off();
        ESP_LOGD("integra", "ISCP MATCH: Main Power OFF");
      }
    }
  }
};