// Prefer the real ESP32 WiFi header when building for ESP32.
#if defined(ARDUINO_ARCH_ESP32)
#if __has_include(<Arduino.h>)
#include <Arduino.h>
#endif
#if __has_include(<WiFi.h>)
#include <WiFi.h>
#endif
#else

// Provide minimal stubs so editors/IDEs that can't find WiFi.h
// won't show include-errors. These stubs are only used when
// building off-target and will be ignored on ESP32.
#if __has_include(<Arduino.h>)
#include <Arduino.h>
#else
class String {
public:
  String(const char *) {}
};

struct SerialClass {
  void begin(unsigned long) {}
  void println(const String &) {}
};

static SerialClass Serial;
#endif
namespace WiFi {
  inline void mode(int) {}
  inline String macAddress() { return String("00:00:00:00:00:00"); }
}
constexpr int WIFI_STA = 0;
#endif

void setup() {
  Serial.begin(115200);
  WiFi::mode(WIFI_STA);
  Serial.println(WiFi::macAddress());
}

void loop() {}