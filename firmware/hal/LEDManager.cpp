#include "LEDManager.h"
#include "CurrentTimeManager.h"

LEDManager::LEDManager(const MCP23S17& mcp, bool gpioA, int numLEDs) :
    mcp23S17(mcp), isgpioA(gpioA), numLEDs(numLEDs)
{
    if (gpioA)
    {
        mcp23S17.enable_pullups_gpioa(false);
        mcp23S17.set_pin_mode_gpioa(MCP23S17::PIN_MODE_OUTPUT);
    }
    else
    {
        mcp23S17.enable_pullups_gpiob(false);
        mcp23S17.set_pin_mode_gpiob(MCP23S17::PIN_MODE_OUTPUT);
    }

    for (int i = 0; i < numLEDs; ++i)
    {
        lastUpdateTimes[i] = 0;
        states[i] = OFF;
        setLEDState(i, false);
    }
}

// Method to turn on the LED
void LEDManager::on(int ledIndex) 
{
    if (ledIndex < numLEDs)
    {
        setLEDState(ledIndex, true);
        states[ledIndex] = ON;
    }
}

// Method to turn off the LED
void LEDManager::off(int ledIndex)
{
    if (ledIndex < numLEDs)
    {
        setLEDState(ledIndex, false);
        states[ledIndex] = OFF;
    }
}

// Switch to the "constant long blink" mode.
void LEDManager::longBlink(int ledIndex)
{
    if (ledIndex < numLEDs) {
        blinkOnTimes[ledIndex] = LONG_BLINK_ON_TIME;
        blinkOffTimes[ledIndex] = LONG_BLINK_OFF_TIME;
        states[ledIndex] = BLINK;
    }
}

void LEDManager::shortBlink(int ledIndex)
{
    if (ledIndex < numLEDs)
    {
        blinkOnTimes[ledIndex] = SHORT_BLINK_ON_TIME;
        blinkOffTimes[ledIndex] = SHORT_BLINK_ON_TIME;
        states[ledIndex] = BLINK;
    }
}

void LEDManager::errorBlink(int ledIndex)
{
    if (ledIndex < numLEDs) 
    {
        blinkOnTimes[ledIndex] = ERROR_BLINK_ON_TIME;
        blinkOffTimes[ledIndex] = ERROR_BLINK_OFF_TIME;
        blinkCounts[ledIndex] = ERROR_BLINK_COUNT;
        states[ledIndex] = ERROR_BLINK;
    }
}

// Stop the blinkin mode.
void LEDManager::stopBlinking(int ledIndex)
{
    if (ledIndex < numLEDs)
    {
        states[ledIndex] = OFF;
        setLEDState(ledIndex, false);
    }
}

void LEDManager::update()
{
    uint32_t currentTime = CurrentTimeManager::millis();
    for (int i = 0; i < numLEDs; ++i)
    {
        uint32_t elapsed = currentTime - lastUpdateTimes[i];

        switch (states[i])
        {
            case ON:
                // LED is already ON, nothing to do
                break;
            case OFF:
                // LED is already OFF, nothing to do
                break;
            case BLINK:
                if (elapsed >= blinkOnTimes[i] && ledStates[i] == true)
                {
                    setLEDState(i, false);
                    lastUpdateTimes[i] = currentTime;
                } else if (elapsed >= blinkOffTimes[i] && ledStates[i] == false)
                {
                    setLEDState(i, true);
                    lastUpdateTimes[i] = currentTime;
                }
                break;
            case ERROR_BLINK:
                if (blinkCounts[i] > 0) {
                    if (elapsed >= blinkOnTimes[i] && ledStates[i] == true) 
                    {
                        setLEDState(i, false);
                        lastUpdateTimes[i] = currentTime;
                        blinkCounts[i]--;
                    } else if (elapsed >= blinkOffTimes[i] && ledStates[i] == false)
                    {
                        setLEDState(i, true);
                        lastUpdateTimes[i] = currentTime;
                    }
                } else
                {
                    states[i] = OFF;
                    setLEDState(i, false);
                }

                break;
        }
    }
}

// Call the low-level library to turn LED on or off.
void LEDManager::setLEDState(int ledIndex, bool state)
{
    ledStates[ledIndex] = state;

    if (isgpioA)
    {
        mcp23S17.write_pin_gpioa(ledIndex, state);
    }
    else
    {
        mcp23S17.write_pin_gpiob(ledIndex, state);
    }
}
