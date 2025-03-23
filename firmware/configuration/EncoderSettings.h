#ifndef ENCODERSETTINGS_H
#define ENCODERSETTINGS_H

#include "BaseSettings.h"

class EncoderSettings : public BaseSettings {
public:
    EncoderSettings();
    void reset() override;
    size_t load(const uint8_t* data) override;
    size_t save(uint8_t* data) const override;

    double encoderMultiplier;
};

#endif // ENCODERSETTINGS_H