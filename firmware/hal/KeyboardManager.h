#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "..\lowlevel\MCP23S17.h"

// Max keys supported.
#define MAX_KEYS_COUNT 16

// Debounce time for the button, in msec
#define DEBOUNCE_TIME 20

class KeyboardManager {
public:
    KeyboardManager(MCP23S17& mcp, bool gpioA, int numKeys);

    // timeSincePressed contains the time since the button is pressed.
    bool isKeyPressed(int keyIndex, uint32_t& timeSincePressed);

    // Return true once only until the key is released and pressed again.
    bool isKeyStateChanged(int keyIndex, bool& newState);

    // this one used to detect "ON" state only.
    bool isKeyStateChanged(int keyIndex);

private:
    MCP23S17& mcp;

    bool gpioA;
    uint8_t numKeys;
    const uint16_t debounce_time;

    bool last_key_states[MAX_KEYS_COUNT];
    bool last_key_state_changed[MAX_KEYS_COUNT];
    uint32_t last_debounce_times[MAX_KEYS_COUNT];
};

#endif // KEYBOARD_MANAGER_H