#include "KeyboardManager.h"
#include "pico/stdlib.h"

#include "CurrentTimeManager.h"

KeyboardManager::KeyboardManager(MCP23S17& mcp, bool gpioA, int numKeys)
    : mcp(mcp), gpioA(gpioA), numKeys(numKeys), debounce_time(DEBOUNCE_TIME)
{
    for (int i = 0; i < numKeys && i < MAX_KEYS_COUNT; ++i)
    {
        last_key_states[i] = false;
        last_key_state_changed[i] = false;
        last_debounce_times[i] = 0;
    }

    // Configure GPIOs.
    if (gpioA)
    {
        mcp.enable_pullups_gpioa(true);
        mcp.set_pin_mode_gpioa(MCP23S17::PIN_MODE_INPUT);
    }
    else
    {
        mcp.enable_pullups_gpiob(true);
        mcp.set_pin_mode_gpiob(MCP23S17::PIN_MODE_INPUT);
    }
}

bool KeyboardManager::isKeyPressed(int keyIndex, uint32_t& timeSincePressed)
{
    timeSincePressed = 0;

    if (keyIndex < 0 || keyIndex >= numKeys || keyIndex >= MAX_KEYS_COUNT)
    {
        return false;
    }

    uint8_t key_state = gpioA ? mcp.read_register(MCP23S17::GPIOA) :
        mcp.read_register(MCP23S17::GPIOB);  // GPIOA or GPIOB register
    key_state = ~key_state; // since the keys are connected to ground

    uint32_t current_time = CurrentTimeManager::millis();
    uint8_t key_mask = 1 << keyIndex;

    bool curKeyState = key_state & key_mask; // current state
    bool lastKeyState = last_key_states[keyIndex];// previous state
    if (curKeyState != lastKeyState)
    {
        last_key_states[keyIndex] = curKeyState;
        last_debounce_times[keyIndex] = current_time;
        last_key_state_changed[keyIndex] = true;
    }

    timeSincePressed = current_time - last_debounce_times[keyIndex];
    if (timeSincePressed > debounce_time)
    {
        // Still keeping the same state, so the button was indeed pressed/unpressed.
        return curKeyState;
    }

    // Not yet...
    return false;
}

// this one used to detect "ON" state only, for convenience
bool KeyboardManager::isKeyStateChanged(int keyIndex)
{
    bool newState = false;
    return isKeyStateChanged(keyIndex, newState) & newState;
}

bool KeyboardManager::isKeyStateChanged(int keyIndex, bool& newState)
{
    if (!last_key_state_changed[keyIndex]) return false;

    newState = last_key_states[keyIndex];
    last_key_state_changed[keyIndex] = false;

    return true;
}
