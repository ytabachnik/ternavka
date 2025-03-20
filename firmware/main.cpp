#include "pico/stdlib.h"
#include "lowlevel/MCP23S17.h"
#include <stdio.h>

#include "hal/LEDManager.h"
#include "hal/KeyboardManager.h"

#define CS_PIN 5 // pin 7 on Pico
#define SPI_PORT spi0
#define MCP23S17_ADDR 0x20

// Function to get the current time in milliseconds
uint32_t getCurrentTimeMillis()
{
    return to_ms_since_boot(get_absolute_time());
}

const int LEDS_COUNT = 8;
const int KEYS_COUNT = 8;

const int MAX_LED_STATE = 4;

struct LEDState
{
    int index;
    bool isChanged;
    bool keyHandled;
};

/// @brief Read the LED states from keyboard.
/// @param ledStates 
/// @param kybdManager 
void ReadLEDStates(LEDState* ledStates, KeyboardManager& kybdManager)
{
    for (int i = 0; i < KEYS_COUNT; i ++)
    {
        if (kybdManager.is_key_pressed(i))
        {
            // Waiting for key release before the mode change.
            if (ledStates[i].keyHandled) continue;

            ledStates[i].isChanged = true;
            ledStates[i].keyHandled = true;

            ledStates[i].index ++;
            if (ledStates[i].index > MAX_LED_STATE)
            {
                ledStates[i].index = 0;
            }
        }
        else
        {
            ledStates[i].keyHandled = false;
        }
    }
}

/// @brief Update LED states on the LEDs themselves.
void UpdateLEDStates(LEDState* ledStates, LEDManager& ledManager)
{
    for (int i = 0; i < LEDS_COUNT; i ++)
    {
        // Do not touch states if the button wasn't pressed.
        if (false == ledStates[i].isChanged) continue;
 
        ledStates[i].isChanged = false;
        int ledState = ledStates[i].index;
        switch (ledState)
        {
            case 0: ledManager.off(i); break;
            case 1: ledManager.longBlink(i); break;
            case 2: ledManager.shortBlink(i); break;
            case 3: ledManager.errorBlink(i); break;
            case 4: ledManager.on(i); break;;

            default: break;
        }
    }
}

int main()
{
    stdio_init_all();
    MCP23S17 mcp23s17(CS_PIN, SPI_PORT, MCP23S17_ADDR);

    KeyboardManager kybdManager(mcp23s17, true, KEYS_COUNT);
    LEDManager ledManager(mcp23s17, false, LEDS_COUNT);

    LEDState ledStates[LEDS_COUNT];
    for (int8_t i = 0; i < KEYS_COUNT; i ++)
    {
        ledStates[i].index = 0;
        ledStates[i].isChanged = false;
    }

    while (true)
    {
        uint32_t ms_since_boot = to_ms_since_boot(get_absolute_time());
        ledManager.update(ms_since_boot);

        ReadLEDStates(ledStates, kybdManager);
        UpdateLEDStates(ledStates, ledManager);
    }

    return 0;
}