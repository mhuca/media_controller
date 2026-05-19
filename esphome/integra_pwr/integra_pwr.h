#include "esphome.h"

namespace esphome {
namespace integra {

class IntegraPwrListener : public Component {
  public:
  WiFiClient client;
  const char* integra_ip = "10.0.168.212"; 
  const uint16_t port = 60128;
  uint32_t off_requested_at = 0;
  bool off_pending = false;
  //const uint32_t sustain_ms = 120000; 

  void setup() override {
    ESP_LOGI("integra", "Sovereign Link: Monitoring Trigger A at %s", integra_ip);
  }

  void loop() override {
    // Pull values dynamically from the YAML entities
    std::string current_ip = id(integra_ip_addr).state;
    uint16_t current_port = (uint16_t)id(integra_port_num).state;
    uint32_t sustain_ms = (uint32_t)(id(amp_sustain_minutes).state * 60.0 * 1000.0);

    // 1. Connection Management & Change Detection
    if (client.connected()) {
      // If the UI changed the IP while we are connected, drop and move
      if (client.remoteIP().toString() != current_ip.c_str()) {
        ESP_LOGW("integra", "Target IP changed in UI. Pivoting...");

        client.stop();
      }
    }

    if (!client.connected()) {
      static uint32_t last_reconnect = 0;
      if (millis() - last_reconnect > 15000) {
        last_reconnect = millis();
        ESP_LOGD("integra", "Connecting to %s:%u...", current_ip.c_str(), current_port);
        client.connect(current_ip.c_str(), current_port);
      }
      return;
    }

    // Process all available data
    while (client.available()) {
      char c = client.read();
      static String buffer = "";
      buffer += c;
      if (buffer.length() > 25) buffer = buffer.substring(1); 

      if (buffer.indexOf("!1TGA01") != -1) {
        off_pending = false;
        id(relay_template).turn_on();
        // 1. Local Log
        ESP_LOGI("integra", "eISCP MATCH: Trigger A HIGH (Power ON)");

        buffer = ""; 
      } 
      else if (buffer.indexOf("!1TGA00") != -1) {
        if (!off_pending) {
          off_requested_at = millis();
          off_pending = true;
          // Local Log
          ESP_LOGI("integra", "eISCP: Trigger A LOW. Cooling down for %.1f minutes", id(amp_sustain_minutes).state);

        }
        buffer = "";
      }
    }

    // Check sustain timer
    if (off_pending && (millis() - off_requested_at > sustain_ms)) {
      id(relay_template).turn_off();
      off_pending = false;
      ESP_LOGI("integra", "eISCP TIMER: Sustain ended. Powering OFF.");
    }
  }
};

// Global instance for direct access
static IntegraPwrListener *integra_global = new IntegraPwrListener();

} // namespace integra
} // namespace esphome