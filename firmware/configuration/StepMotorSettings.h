#ifndef STEPMOTORSETTINGS_H
#define STEPMOTORSETTINGS_H

#include "BaseSettings.h"

class StepMotorSettings : public BaseSettings {
public:
    StepMotorSettings();
    void reset() override;
    size_t load(const uint8_t* data) override;
    size_t save(uint8_t* data) const override;

    int stepMotorSpeed;
    int stepMotorAcceleration;
};

#endif // STEPMOTORSETTINGS_H
