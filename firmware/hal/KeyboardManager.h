#ifndef KEYBOARD_MANAGER_H
#define KEYBOARD_MANAGER_H

#include "..\lowlevel\MCP23S17.h"

// Debounce time for the button, in msec
#define DEBOUNCE_TIME 20

class KeyboardManager 
{
    static const int8_t MAX_KEYS_COUNT = 8;

public:
    // System key ID.
    enum class KeyID
    {
        Key0 = 0,
        Key1 = 1,
        Key2 = 2,
        Key3 = 3,

        Key4 = 4,
        Key5 = 5,
        Key6 = 6,
        Key7 = 7,
        VALUE_COUNT = 8 // This helps in determining the number of enum values
    };

public:
    KeyboardManager(MCP23S17& mcp, bool gpioA, int numKeys);

    // timeSincePressed contains the time since the button is pressed.
    bool isKeyPressed(KeyID keyID, uint32_t& timeSincePressed);

    // Return true once only until the key is released and pressed again.
    bool isKeyStateChanged(KeyID keyID, bool& newState);

    // this one used to detect "ON" state only.
    bool isKeyStateChanged(KeyID keyID);

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