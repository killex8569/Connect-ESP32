#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);

void setup() {
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  Serial.println("Hello, world!");
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}