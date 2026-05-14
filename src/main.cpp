#include <esp_now.h>// https://github.com/espressif/esp-idf/blob/master/components/esp_wifi/include/esp_now.h
#include <WiFi.h>

uint8_t broadcastAddress[] = {0x8C, 0x4F, 0x00, 0x28, 0x40, 0xE4}; // MAC du receveur 

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;
struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print(F("\r\n Master packet sent:\t"));
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println(F("Error initializing ESP-NOW"));
    return;
  }
  Serial.print(F("Transmitter initialized : "));
  Serial.println(WiFi.macAddress());
  
  // Define Send function
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println(F("Failed to add peer"));
    return;
  }
}

void loop() {
  // Set values to send
  strcpy(myData.a, "data type char");
  myData.b = random(1, 20);
  myData.c = 1.2;
  myData.d = "hello";
  myData.e = false;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.println(F("Sent with success"));
  }
  else {
    Serial.println(F("Error sending the data"));
  }
  delay(1000);
}
