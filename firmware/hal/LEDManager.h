#ifndef LEDMANAGER_H
#define LEDMANAGER_H

#include <stdint.h>
#include "..\lowlevel\MCP23S17.h"

class LEDManager {
private:
    // Constants for blink timings (all in ms)
    const int LONG_BLINK_ON_TIME = 500;
    const int LONG_BLINK_OFF_TIME = 500;

    const int SHORT_BLINK_ON_TIME = 100;
    const int SHORT_BLINK_OFF_TIME = 100;

    const int ERROR_BLINK_ON_TIME = 50;
    const int ERROR_BLINK_OFF_TIME = 50;
    const int ERROR_BLINK_COUNT = 3;

    // Maximum number of LEDs
    static const int MAX_LEDS = 16;

public:
    // Constructor to initialize LED controller with hardwire level.
    LEDManager(const MCP23S17& mcp, bool gpioA, int numLEDs);

    // Call this in the main app loop.
    void update();

    // Methods to control LED states
    void on(int ledIndex);
    void off(int ledIndex);
    void longBlink(int ledIndex);
    void shortBlink(int ledIndex);
    void errorBlink(int ledIndex);
    void stopBlinking(int ledIndex);

private:
    // Hardwire controller.
    MCP23S17 mcp23S17;

    // Whether the LEDs are conected to the GPIO A?
    bool isgpioA;

    // Enumeration for LED states
    enum State { ON, OFF, BLINK, ERROR_BLINK };

    // Arrays to store LED configurations and states
    int numLEDs;

    State states[MAX_LEDS];
    int blinkOnTimes[MAX_LEDS];
    int blinkOffTimes[MAX_LEDS];
    int blinkCounts[MAX_LEDS];
    bool ledStates[MAX_LEDS];
    uint32_t lastUpdateTimes[MAX_LEDS];

    // Method to set LED state using external low-level library
    void setLEDState(int ledIndex, bool state);
};

#endif // LEDMANAGER_H