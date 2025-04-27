#include "Arduino.h"

bool EB_read(uint8_t pin) {
    auto result = digitalRead(pin);
    return result;
}

void EB_mode(uint8_t pin, uint8_t mode) {
    pinMode(pin, mode);
}

uint32_t EB_uptime() {
    return millis();
}
