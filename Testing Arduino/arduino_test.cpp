#include <Arduino.h>

int absolute(int x) {
    return x < 0 ? -x : x;  // Returns -x if x is negative; otherwise, returns x.
}

void setup() {
    Serial.begin(9600);  // Start the serial communication at 9600 baud rate
    int result = absolute(-5);  // Call the absolute function with -5
    Serial.println(result);     // Print the result to the serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:

}

/// home/codespace/Documents/PlatformIO/Projects/250126-143251-arduino-blink