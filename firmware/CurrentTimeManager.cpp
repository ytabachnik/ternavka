#include "CurrentTimeManager.h"
#include "time.h"

// Initialize the static member variable
uint32_t CurrentTimeManager::msecSinceBoot = 0;

// Method to update the internal time variable
void CurrentTimeManager::update()
{
    msecSinceBoot = to_ms_since_boot(get_absolute_time());
}

// Method to get the current milliseconds since boot
uint32_t CurrentTimeManager::millis()
{
    return msecSinceBoot;
}
