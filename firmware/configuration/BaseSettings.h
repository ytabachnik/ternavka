#ifndef BASESETTINGS_H
#define BASESETTINGS_H

#include <pico/stdlib.h>

class BaseSettings {
public:
    virtual void reset() = 0; // Pure virtual function to be implemented by derived classes

    virtual size_t load(const uint8_t* data) = 0;
    virtual size_t save(uint8_t* data) const = 0;};

#endif // BASESETTINGS_H