#include "FeedSettings.h"
#include <cstring>

FeedSettings::FeedSettings() {
    reset();
}

void FeedSettings::reset() {
    forwardFeedSpeed = 100; // Default value
    backFeedSpeed = 100;    // Default value
    forwardFeedStep = 1;    // Default value
    backFeedStep = 1;       // Default value
}

size_t FeedSettings::load(const uint8_t* data) {
    std::memcpy(this, data, sizeof(FeedSettings));
    return sizeof(FeedSettings);
}

size_t FeedSettings::save(uint8_t* data) const {
    std::memcpy(data, this, sizeof(FeedSettings));
    return sizeof(FeedSettings);
}