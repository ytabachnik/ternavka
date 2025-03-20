#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "..\lowlevel\MCP23S17.h"

// Max keys supported.
#define MAX_KEYS_COUNT 16

// Debounce time for the button, in msec
#define DEBOUNCE_TIME 10

class KeyboardManager {
public:
    KeyboardManager(MCP23S17& mcp, bool gpioA, int numKeys);
    bool is_key_pressed(int keyIndex);

private:
    MCP23S17& mcp;

    bool gpioA;
    uint8_t numKeys;
    const uint16_t debounce_time;
    bool last_key_states[MAX_KEYS_COUNT];
    uint32_t last_debounce_times[MAX_KEYS_COUNT];
};

#endif // KEYBOARD_MANAGER_H