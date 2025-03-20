#include "pico/stdlib.h"
#include "MCP23S17.h"
#include <stdio.h>

#include "hal/LEDManager.h"

#define CS_PIN 5 // pin 7 on Pico
#define SPI_PORT spi0
#define MCP23S17_ADDR 0x20

// Function to get the current time in milliseconds
uint32_t getCurrentTimeMillis()
{
    return to_ms_since_boot(get_absolute_time());
}

const int LEDS_COUNT = 8;

int main() {
    stdio_init_all();
    MCP23S17 mcp23s17(CS_PIN, SPI_PORT, MCP23S17_ADDR);

    mcp23s17.enable_pullups_gpioa(true);
    mcp23s17.set_pin_mode_gpioa(0xFF); //input

    LEDManager ledManager(mcp23s17, false, LEDS_COUNT);

    //for (int i = 0; i < LEDS_COUNT; i ++)
    //{
        //ledManager.on(0);
        //ledManager.on(1);
        //ledManager.on(2);
        //ledManager.errorBlink(3);
        ledManager.shortBlink(4);
        ledManager.longBlink(5);

    //ledManager.longBlink(3);

    while (true) 
    {
        uint32_t ms_since_boot = to_ms_since_boot(get_absolute_time());
        printf("Milliseconds since boot: %u\n", ms_since_boot);
        sleep_ms(100);

        ledManager.update(ms_since_boot);
        //uint8_t gpioa_state = mcp23s17.read_gpioa();  // Read GPIOA
        //mcp23s17.write_pin_gpiob(~gpioa_state);
        //sleep_ms(100);
    }

    return 0;
}