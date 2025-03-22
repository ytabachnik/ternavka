#ifndef CURRENT_TIME_MANAGER_H
#define CURRENT_TIME_MANAGER_H

#include <stdio.h>
#include "pico/stdlib.h"


class CurrentTimeManager 
{
public:
    // Method to update the internal time variable
    static void update();

    // Method to get the current milliseconds since boot
    static uint32_t millis();

private:
    // Internal variable to store milliseconds since boot
    static uint32_t msecSinceBoot;
};

#endif // CURRENT_TIME_MANAGER_H