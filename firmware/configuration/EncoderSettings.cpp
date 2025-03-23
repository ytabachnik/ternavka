#include "EncoderSettings.h"
#include <cstring>

EncoderSettings::EncoderSettings() {
    reset();
}

void EncoderSettings::reset() {
    encoderMultiplier = 1.0; // Default value
}

size_t EncoderSettings::load(const uint8_t* data) {
    std::memcpy(this, data, sizeof(EncoderSettings));
    return sizeof(EncoderSettings);
}

size_t EncoderSettings::save(uint8_t* data) const {
    std::memcpy(data, this, sizeof(EncoderSettings));
    return sizeof(EncoderSettings);
}