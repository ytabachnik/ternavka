#include "StepMotorSettings.h"
#include <cstring>

StepMotorSettings::StepMotorSettings() {
    reset();
}

void StepMotorSettings::reset() {
    stepMotorSpeed = 200; // Default value
    stepMotorAcceleration = 50; // Default value
}

size_t StepMotorSettings::load(const uint8_t* data) {
    std::memcpy(this, data, sizeof(StepMotorSettings));
    return sizeof(StepMotorSettings);
}

size_t StepMotorSettings::save(uint8_t* data) const {
    std::memcpy(data, this, sizeof(StepMotorSettings));
    return sizeof(StepMotorSettings);
}