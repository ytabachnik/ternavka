#ifndef FEEDSETTINGS_H
#define FEEDSETTINGS_H

#include "BaseSettings.h"

class FeedSettings : public BaseSettings {
public:
    FeedSettings();
    void reset() override;
    size_t load(const uint8_t* data) override;
    size_t save(uint8_t* data) const override;

    int forwardFeedSpeed;
    int backFeedSpeed;
    int forwardFeedStep;
    int backFeedStep;
};

#endif // FEEDSETTINGS_H