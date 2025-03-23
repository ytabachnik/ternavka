#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "FeedSettings.h"
#include "EncoderSettings.h"
#include "StepMotorSettings.h"

class Configuration {
public:
    Configuration();

    FeedSettings& getFeedSettings();
    EncoderSettings& getEncoderSettings();
    StepMotorSettings& getStepMotorSettings();

    void reset();
    void loadFromFlash();
    void saveToFlash();

private:
    FeedSettings feedSettings;
    EncoderSettings encoderSettings;
    StepMotorSettings stepMotorSettings;

    static constexpr uint32_t FLASH_TARGET_OFFSET = 256 * 1024; // Offset in flash memory
};

#endif // CONFIGURATION_H