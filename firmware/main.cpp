#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/spi.h"

#include "lowlevel/MCP23S17.h"
#include "lowlevel/TCA9548A.h"

#include "hal/LEDManager.h"
#include "hal/KeyboardManager.h"
#include "hal/MultiDisplayManager.h"

// SPI configuration.
// Constants for SPI pins
#define KYBD_SPI_PORT spi0
#define KYBD_SPI_SCK 18 // Physical pin 24
#define KYBD_SPI_MOSI_PIN 19 // Physical pin 25
#define KYBD_SPI_MISO_PIN 16 // Physical pin 21

#define KYBD_SPI_CS_PIN 5 // Physical pin 7

// An addr of the MCP23S17 controller, when A0, A1, A2 are set to 0.
#define KYBD_MCP23S17_ADDR 0x20

// I2C configuration.
#define DISPLAY_I2C_PORT i2c1
#define DISPLAY_I2C_SDA 2 // default SDA pin for I2C1, plysical pin 4
#define DISPLAY_I2C_SCL 3 // default SCL pin for I2C1, plysical pin 5

// Default addr of OLED display.
#define DISPLAY_DEFAULT_ADDR 0x3c

// Default address of TCA9548 extender
#define DISPLAY_EXTENDER_ADDR 0x70

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

/// @brief Initialize the I2C part.
void initializeI2C()
{
    i2c_init(DISPLAY_I2C_PORT, 100 * 1000); // Initialize I2C at 100kHz
    gpio_set_function(DISPLAY_I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(DISPLAY_I2C_SDA);
    gpio_pull_up(DISPLAY_I2C_SCL);
}

/// @brief Initialize the SPI part.
void initializeSPI()
{
    spi_init(KYBD_SPI_PORT, 1000 * 1000);  // 1 MHz
    gpio_set_function(KYBD_SPI_SCK, GPIO_FUNC_SPI);  // SCK
    gpio_set_function(KYBD_SPI_MOSI_PIN, GPIO_FUNC_SPI);  // MOSI
    gpio_set_function(KYBD_SPI_MISO_PIN, GPIO_FUNC_SPI);  // MISO

    gpio_init(KYBD_SPI_CS_PIN);
    gpio_set_dir(KYBD_SPI_CS_PIN, GPIO_OUT);
    gpio_put(KYBD_SPI_CS_PIN, 1);  // CS high
}

int main()
{
    stdio_init_all();

    initializeI2C();
    initializeSPI();

    // Low-level
    MCP23S17 mcp23s17(KYBD_SPI_CS_PIN, KYBD_SPI_PORT, KYBD_MCP23S17_ADDR);
    TCA9548A i2cExtender(DISPLAY_I2C_PORT, DISPLAY_EXTENDER_ADDR);

    // HAL.
    KeyboardManager kybdManager(mcp23s17, true, KEYS_COUNT);
    LEDManager ledManager(mcp23s17, false, LEDS_COUNT);


    MultiDisplayManager displayManager(i2cExtender, 128, 64, DISPLAY_DEFAULT_ADDR,
        DISPLAY_I2C_PORT);

    displayManager.setActiveDisplay(0);
    displayManager.clear();
    displayManager.drawStringCentered(10, 1, "MAUUU");
    displayManager.show();

    displayManager.setActiveDisplay(1);
    displayManager.clear();
    displayManager.drawStringCentered(10, 2, "MRRR");
    displayManager.show();

    displayManager.setActiveDisplay(2);
    displayManager.clear();
    displayManager.drawStringCentered(10, 3, "MIII");
    displayManager.show();

    /*
    ssd1306_t oled;
    oled.external_vcc=true;
    bool res = ssd1306_init(
        &oled,
        128,
        64,
        0x3c,
        DISPLAY_I2C_PORT);

        if (res)
        {
            ssd1306_clear(&oled);
            ssd1306_draw_string_centered(&oled, 10, 1, "MAUUUR");
            ssd1306_show(&oled);
        }
    */

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